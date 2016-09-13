<?php
/*
 * Gigya PHP SDK
 *
 * http://developers.gigya.com/display/GD/PHP
 */

if (!function_exists('curl_init')) {
    throw new Exception('Gigya.Socialize needs the CURL PHP extension.');
}
if (!function_exists('json_decode')) {
    throw new Exception('Gigya.Socialize needs the JSON PHP extension.');
}


/**
 * Gigya Socialize Exception
 */
class GSException extends Exception
{
    public $errorMessage;
}

/**
 * Gigya Socialize Key Not Found Exception
 */
class GSKeyNotFoundException extends GSException
{
    public function __construct($key)
    {
        $this->errorMessage = "GSObject does not contain a value for key " . $key;
    }
}


/**
 * A Request to Gigya Socialize API
 */
class GSRequest
{
    private static $cafile;
    const DEFAULT_API_DOMAIN = "us1.gigya.com";
    const version = "2.15.8";

    private $host;
    private $domain;
    private $path;
    private $traceLog = array();
    protected $method;
    private $proxy;
    private $proxyType = CURLPROXY_HTTP;
    private $proxyUserPass = ":";
    private $curlArray = array();

    private $apiKey;
    private $userKey;
    private $secretKey;
    private $params; //GSObject
    private $useHTTPS;
    private $apiDomain = self::DEFAULT_API_DOMAIN;


    static function __constructStatic()
    {
        GSRequest::$cafile = realpath('./cacert.pem');
    }

    /**
     * Constructs a request using an apiKey and secretKey.
     * You must provide a user ID (UID) of the tage user.
     * Suitable for calling our old REST API
     *
     * @param apiKey
     * @param secretKey
     * @param apiMethod the api method (including namespace) to call. for example: socialize.getUserInfo
     * If namespaces is not supplied "socialize" is assumed
     * @param params the request parameters
     * @param useHTTPS useHTTPS set this to true if you want to use HTTPS.
     * @param userKey userKey A key of an admin user with extra permissions.
     * If this parameter is provided, then the secretKey parameter is assumed to be the admin user's secret key and not the site's secret key.
     */
    public function __construct($apiKey, $secretKey, $apiMethod, $params = null, $useHTTPS = false, $userKey = null)
    {
        if (!isset($apiMethod) || strlen($apiMethod) == 0)
            return;

        if (substr($apiMethod, 0, 1) == "/")
            $apiMethod = substr($apiMethod, 1);

        if (strrpos($apiMethod, ".") == 0) {
            $this->domain = "socialize.gigya.com";
            $this->path = "/socialize." . $apiMethod;
        } else {
            $tokens = explode(".", $apiMethod);
            $this->domain = $tokens[0] . ".gigya.com";
            $this->path = "/" . $apiMethod;
        }

        $this->method = $apiMethod;

        if (empty($params))
            $this->params = new GSObject();
        else
            $this->params = clone $params;

        // use "_host" to override domain, if available
        $this->domain = $this->params->getString("_host", $this->domain);

        $this->useHTTPS = $useHTTPS;

        $this->apiKey = $apiKey;
        $this->secretKey = $secretKey;
        $this->userKey = $userKey;

        $this->traceField("apiMethod", $apiMethod);
        $this->traceField("apiKey", $apiKey);
    }

    public function setParam($param, $val)
    {
        $this->params->put($param, $val);
    }

    public function getParams()
    {
        return $this->params;
    }

    /**
     * Sets the domain used for making API calls. This method provides the option to override the default domain "gigya.com" and specify an alternative data center to be used.
     * Parameters:
     *    $apiDomain - the domain of the data center to be used. For example: "eu1.gigya.com" for Europe data center.
     */
    public function setAPIDomain($apiDomain)
    {
        if (!isset($apiDomain) || strlen($apiDomain) == 0)
            $this->apiDomain = self::DEFAULT_API_DOMAIN;
        else
            $this->apiDomain = $apiDomain;
    }

    public static function setCAFile($filename)
    {
        GSRequest::$cafile = $filename;
    }

    public function setProxy($proxy, $proxyUserPass = ":", $proxyType = CURLPROXY_HTTP)
    {
        $this->proxy = $proxy;
        $this->proxyType = $proxyType;
        $this->proxyUserPass = $proxyUserPass;
        $this->traceField("proxy", $proxy);
        $this->traceField("proxyType", $proxyType);
        $this->traceField("proxyUserPass", $proxyUserPass);
    }

    public function setCurlOptionsArray($curlArray)
    {
        $this->curlArray = $curlArray;
        $this->traceField("curlArray", $curlArray);
    }

    /**
     * Send the request synchronously
     */
    public function send($timeout = null)
    {
        $format = $this->params->getString("format", null);

        if (!strrpos($this->method, ".")) {
            $this->host = "socialize." . $this->apiDomain;
            $this->path = "/socialize." . $this->method;
        } else {
            $tokens = explode(".", $this->method);
            $this->host = $tokens[0] . "." . $this->apiDomain;
            $this->path = "/" . $this->method;
        }

        //set json as default format.
        if (empty($format)) {
            $format = "json";
            $this->setParam("format", $format);
        }
        if (!empty($timeout)) {
            $this->traceField("timeout", $timeout);
        }

        if (empty($this->method) || (empty($this->apiKey) and empty($this->userKey))) {
            return new GSResponse($this->method, null, $this->params, 400002, null, $this->traceLog);
        }

        if ($this->useHTTPS && empty(GSRequest::$cafile)) {
            return new GSResponse($this->method, null, $this->params, 400003, null, $this->traceLog);
        }

        try {
            $this->setParam("httpStatusCodes", "false");

            $this->traceField("userKey", $this->userKey);
            $this->traceField("apiKey", $this->apiKey);
            $this->traceField("apiMethod", $this->method);
            $this->traceField("params", $this->params);
            $this->traceField("useHTTPS", $this->useHTTPS);

            $responseStr = $this->sendRequest("POST", $this->host, $this->path, $this->params, $this->apiKey, $this->secretKey, $this->useHTTPS, $timeout, $this->userKey);

            return new GSResponse($this->method, $responseStr, null, 0, null, $this->traceLog);
        } catch (Exception $ex) {
            $errcode = 500000;
            $errMsg = $ex->getMessage();
            $length = strlen("Operation timed out");
            if ((substr($ex->getMessage(), 0, $length) === "Operation timed out")) {
                $errcode = 504002;
                $errMsg = "Request Timeout";
            }

            return new GSResponse($this->method, null, $this->params, $errcode, $errMsg, $this->traceLog);
        }
    }

    private function sendRequest($method, $domain, $path, $params, $token, $secret, $useHTTPS = false, $timeout = null, $userKey = null)
    {
        $params->put("sdk", "php_" . GSRequest::version);
        //prepare query params
        $protocol = $useHTTPS || empty($secret) ? "https" : "http";
        $resourceURI = $protocol . "://" . $domain . $path;

        //UTC timestamp.
        $timestamp = (string)time();

        //timestamp in milliseconds
        $nonce = ((string)SigUtils::currentTimeMillis()) . rand();
        $httpMethod = "POST";

        if ($userKey) {
            $params->put("userKey", $userKey);
        }

        if (!empty($secret)) {
            $params->put("apiKey", $token);

            $params->put("timestamp", $timestamp);
            $params->put("nonce", $nonce);

            //signature
            $signature = self::getOAuth1Signature($secret, $httpMethod, $resourceURI, $useHTTPS, $params);
            $params->put("sig", $signature);
        } else {
            $params->put("oauth_token", $token);
        }

        //get rest response.
        $res = $this->curl($resourceURI, $params, $timeout);
        return $res;
    }


    private function curl($url, $params, $timeout = null)
    {
        foreach ($params->getKeys() as $key) {
            $value = $params->getString($key);
            $postData[$key] = $value;
        }

        $qs = http_build_query($postData);
        $this->traceField("URL", $url);
        $this->traceField("postData", $qs);

        /* POST */
        $defaults = array(
            CURLOPT_URL => $url,
            CURLOPT_POST => 1,
            CURLOPT_HEADER => 1,
            CURLOPT_POSTFIELDS => $qs,
            CURLOPT_HTTPHEADER => array('Expect:'),
            CURLOPT_RETURNTRANSFER => TRUE,
            CURLOPT_SSL_VERIFYPEER => TRUE,
            CURLOPT_SSL_VERIFYHOST => 2,
            CURLOPT_CAINFO => GSRequest::$cafile,
            CURLOPT_PROXY => $this->proxy,
            CURLOPT_PROXYTYPE => $this->proxyType,
            CURLOPT_PROXYUSERPWD => $this->proxyUserPass,
            CURLOPT_TIMEOUT_MS => $timeout
        );

        $ch = curl_init();
        $mergedCurlArray = ($this->curlArray + $defaults);

        curl_setopt_array($ch, $mergedCurlArray);

        if (!$result = curl_exec($ch)) {
            $err = curl_error($ch);
            throw new Exception($err);
        }

        $header_size = curl_getinfo($ch, CURLINFO_HEADER_SIZE);
        curl_close($ch);

        $header = trim(substr($result, 0, $header_size));
        $body = substr($result, $header_size);

        $headers = explode("\r\n", $header);
        foreach ($headers as $value) {
            $kvp = explode(":", $value);
            if ($kvp[0] == "x-server") {
                $this->traceField("server", $kvp[1]);
                break;
            }
        }

        return $body;
    }

    /**
     * Converts a GSObject to a query string
     * @param params
     * @return string
     */
    public static function buildQS($params)
    {
        $val = null;
        $ret = "";
        foreach ($params->getKeys() as $key) {
            $val = $params->getString($key);
            if (isset($val)) {
                $ret .= "$key=" . urlencode($val);
            }
            $ret .= '&';
        }

        $ret = rtrim($ret, "&");

        return $ret;
    }

    private static function getOAuth1Signature($key, $httpMethod, $url, $isSecureConnection, $requestParams)
    {
        // Create the BaseString.
        $baseString = self::calcOAuth1BaseString($httpMethod, $url, $isSecureConnection, $requestParams);
        return SigUtils::calcSignature($baseString, $key);
    }

    private static function calcOAuth1BaseString($httpMethod, $url, $isSecureConnection, $requestParams)
    {


        $normalizedUrl = "";
        $u = parse_url($url);
        $protocol = strtolower($u["scheme"]);

        if (array_key_exists('port', $u)) {
            $port = $u['port'];
        } else {
            $port = null;
        }

        $normalizedUrl .= $protocol . "://";
        $normalizedUrl .= strtolower($u["host"]);

        if ($port != "" && (($protocol == "http" && $port != 80) || ($protocol == "https" && $port != 443))) {
            $normalizedUrl .= ':' . $port;
        }
        $normalizedUrl .= $u["path"];

        // Create a sorted list of query parameters
        $amp = "";
        $queryString = "";
        $keys = $requestParams->getKeys();
        sort($keys);
        foreach ($keys as $key) {
            $value = $requestParams->getString($key);
            if ($value !== false && $value != "0" && empty($value)) {
                $value = "";
            }

            //curl is sending 1 and 0 when the value is boolean.
            //so in order to create a valid signature we're changing false to 0 and true to 1.
            if ($value === false) $value = "0";
            if ($value === true) $value = "1";
            $queryString .= $amp . $key . "=" . self::UrlEncode($value);
            $amp = "&";
        }

        // Construct the base string from the HTTP method, the URL and the parameters
        $baseString = strtoupper($httpMethod) . "&" . self::UrlEncode($normalizedUrl) . "&" . self::UrlEncode($queryString);
        return $baseString;

    }

    public static function UrlEncode($value)
    {
        if ($value === false) {
            return $value;
        } else {
            return str_replace('%7E', '~', rawurlencode($value));
        }
    }

    private function traceField($name, $value)
    {
        array_push($this->traceLog, $name . "=" . print_r($value, true));
    }
}

GSRequest::__constructStatic();

/**
 * Wraps the server's response.
 * If the request was sent with the format set to "xml", the getData() will return null and you should use getResponseText() instead.
 * We only parse response text into GSObject if request format is set "json" which is the default.
 */
class GSResponse
{
    private $errorCode = 0;
    private $errorMessage = null;
    private $rawData = "";
    private $data; //GSObject
    private static $errorMsgDic;
    private $params = null;
    private $method = null;
    private $traceLog = null;


    public static function Init()
    {
        self::$errorMsgDic = new GSObject();
        self::$errorMsgDic->put(400002, "Required parameter is missing");
        self::$errorMsgDic->put(400003, "You must set a certificate for HTTPS requests");
        self::$errorMsgDic->put(500000, "General server error");
    }

    public function getErrorCode()
    {
        return $this->errorCode;
    }

    public function getErrorMessage()
    {
        if (isset($this->errorMessage))
            return $this->errorMessage;
        else {

            if ($this->errorCode == 0 || !self::$errorMsgDic->containsKey((int)$this->errorCode))
                return "";
            else
                return self::$errorMsgDic->getString($this->errorCode);
        }
    }

    public function getResponseText()
    {
        return $this->rawData;
    }

    public function getData()
    {
        return $this->data;
    }

    /* GET BOOLEAN */
    public function getBool($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return $this->data->getBool($key, $defaultValue);
    }

    /* GET INTEGER */
    public function getInt($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return $this->data->getInt($key, $defaultValue);
    }

    /* GET LONG */
    public function getLong($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return $this->data->getLong($key, $defaultValue);
    }

    /* GET INTEGER */
    public function getDouble($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return $this->data->getDouble($key, $defaultValue);
    }

    /* GET STRING */
    public function getString($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return $this->data->getString($key, $defaultValue);
    }

    /* GET GSOBJECT */
    public function getObject($key)
    {
        return $this->data->getObject($key);
    }

    /* GET GSOBJECT[] */
    public function getArray($key)
    {
        return $this->data->getArray($key);
    }

    /* C'tor */
    public function __construct($method, $responseText = null, $params = null, $errorCode = null, $errorMessage = null, $traceLog = null)
    {
        $this->traceLog = $traceLog;
        $this->method = $method;
        if (empty($params))
            $this->params = new GSObject();
        else
            $this->params = $params;

        if (!empty($responseText)) {
            $this->rawData = $responseText;
            if (strpos(ltrim($responseText), "{") !== false) {
                $this->data = new GSObject($responseText);
                if (isset($this->data)) {
                    if ($this->data->containsKey("errorCode")) {
                        $this->errorCode = $this->data->getInt("errorCode");
                    }
                    if ($this->data->containsKey("errorMessage")) {
                        $this->errorMessage = $this->data->getString("errorMessage");
                    }
                }
            } else {
                $matches = array();
                preg_match("~<errorCode\s*>([^<]+)~", $this->rawData, $matches);
                if (sizeof($matches) > 0) {
                    $errCodeStr = $matches[1];
                    if ($errCodeStr != null) {
                        $this->errorCode = (int)$errCodeStr;

                        $matches = array();
                        preg_match("~<errorMessage\s*>([^<]+)~", $this->rawData, $matches);
                        if (sizeof($matches) > 0) {
                            $this->errorMessage = $matches[1];
                        }
                    }
                }
            }

        } else {

            $this->errorCode = $errorCode;
            $this->errorMessage = $errorMessage != null ? $errorMessage : self::getErrorMessage();
            $this->populateClientResponseText();
        }
    }

    private function populateClientResponseText()
    {
        if ($this->params->getString("format", "json")) {
            $this->rawData = "{errorCode:" . $this->errorCode . ",errorMessage:\"" . $this->errorMessage . "\"}";
        } else {
            $sb = array(
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
            , "<" . $this->method . "Response xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"urn:com:gigya:api http://socialize-api.gigya.com/schema\" xmlns=\"urn:com:gigya:api\">"
            , "<errorCode>" . $this->errorCode . "</errorCode>"
            , "<errorMessage>" . $this->errorMessage . "</errorMessager>"
            , "</" . $this->method . "Response>"
            );

            $this->rawData = implode("\r\n", $sb);
        }
    }

    public function getLog()
    {
        return implode("\r\n", $this->traceLog);
    }

    public function __toString()
    {
        $sb = "";
        $sb .= "\terrorCode:";
        $sb .= $this->errorCode;
        $sb .= "\n\terrorMessage:";
        $sb .= $this->errorMessage;
        $sb .= "\n\tdata:";
        $sb .= $this->data;
        return $sb;
    }
}

GSResponse::Init();


/**
 * Used for passing parameters when issueing requests e.g. GSRequest.send
 * As well as returning response data e.g. GSResponse.getData
 *
 * @version 1.0
 */
class GSObject
{
    private $map;

    /* PUBLIC INTERFACE */

    /**
     * Construct a GSObject from json string, throws excpetion.
     *
     * @param string|object the json formatted string
     * @throws Exception if unable to parse json
     */
    public function __construct($json = null)
    {
        $this->map = array();
        if (!empty($json)) {

            //parse json string.
            if (gettype($json) == 'string') {
                $obj = json_decode($json, false);


                if ($obj == null) {
                    throw new GSException();
                }
            } else {
                $obj = $json;
            }

            self::processJsonObject($obj, $this);
        }
    }

    public function serialize()
    {
        $arr = Array();
        if (empty($this->map)) return $arr;

        $arr = $this->serializeGSObject($this);

        return $arr;
    }

    public static function serializeGSObject($gsd)
    {
        $arr = Array();
        foreach ($gsd->map as $name => $value) {

            $val = GSObject::serializeValue($value);
            $arr[$name] = $val;
        }
        return $arr;
    }

    public static function serializeValue($value)
    {
        //GSDictionary
        if ($value instanceof GSObject) {
            return GSObject::serializeGSObject($value);
        } //array
        else if ($value instanceof GSArray) {
            return GSArray::serializeGSArray($value);
        } //else just add
        else {
            return $value;
        }
    }

    /* Put */
    const DEFAULT_VALUE = '@@EMPTY@@';

    public function put($key, $value)
    {
        $this->map[$key] = $value;
    }

    private function get($key, $defaultValue)
    {
        if (array_key_exists($key, $this->map)) {
            return $this->map[$key];
        }

        if ($defaultValue !== GSObject::DEFAULT_VALUE) {
            return $defaultValue;
        }
        throw new GSKeyNotFoundException($key);
    }

    /* GET BOOLEAN */
    public function getBool($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return (bool)$this->get($key, $defaultValue);
    }

    /* GET INTEGER */
    public function getInt($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return (int)$this->get($key, $defaultValue);
    }

    /* GET LONG */
    public function getLong($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return (float)$this->get($key, $defaultValue);
    }

    /* GET DOUBLE */
    public function getDouble($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        return (double)$this->get($key, $defaultValue);
    }

    /* GET STRING */
    public function getString($key, $defaultValue = GSObject::DEFAULT_VALUE)
    {
        $obj = $this->get($key, $defaultValue);
        return (string)$obj;
    }

    /* GET GSOBJECT */
    public function getObject($key)
    {
        return (object)$this->get($key, null);
    }

    /* GET GSOBJECT[] */
    public function getArray($key)
    {
        return $this->get($key, null);
    }

    /**
     * Parse parameters from URL into the dictionary
     *
     * @param url
     */
    public function parseURL($url)
    {
        try {
            $u = parse_url($url);
            if (isset($u["query"]))
                $this->parseQueryString($u["query"]);
            if (isset($u["fragment"]))
                $this->parseQueryString($u["fragment"]);
        } catch (Exception $e) {
        }
    }


    /**
     * Parse parameters from query string
     *
     * @param qs
     */
    public function parseQueryString($qs)
    {
        if (!isset($qs)) return;
        parse_str($qs, $this->map);
    }

    public function containsKey($key)
    {
        return array_key_exists($key, $this->map);
    }

    public function remove($key)
    {
        unset($this->map[$key]);
    }

    public function clear()
    {
        unset($this->map);
        $this->map = array();
    }

    public function getKeys()
    {
        return array_keys($this->map);
    }

    public function __toString()
    {
        return $this->toJsonString();
    }

    public function toString()
    {
        return $this->toJsonString();
    }

    public function toJsonString()
    {
        try {
            return json_encode($this->serialize());
        } catch (Exception $e) {
            return null;
        }
    }

    private static function processJsonObject($jo, $parentObj)
    {
        if (!empty($jo))
            foreach ($jo as $name => $value) {
                //array
                if (is_array(($value))) {
                    $parentObj->put($name, new GSArray($value));
                } //object
                elseif (is_object($value)) {
                    $childObj = new GSObject();
                    $parentObj->put($name, $childObj);
                    self::processJsonObject($value, $childObj);
                } //primitive
                else {
                    $parentObj->put($name, $value);
                }
            }

        return $parentObj;

    }
}

class GSArray
{
    private $map;
    const NO_INDEX_EX = "GSArray does not contain a value at index ";


    public function __construct($value = null)
    {
        $this->map = array();
        if (!empty($value)) {
            $obj = $value;

            //parse json string.
            if (gettype($value) == 'string') {
                $obj = json_decode($value, false);

                if ($obj == null) {
                    throw new GSException();
                }
            }

            $this->processJsonObject($obj, $this);
        }
    }

    private static function processJsonObject($value, $gsarr)
    {
        if (!empty($value)) {
            foreach ($value as $val) {
                if ($val == null) {
                    $gsarr->add($val);
                } elseif (is_object($val)) {
                    $gsobj = new GSObject($val);
                    $gsarr->add($gsobj);
                } else if (is_array(($val))) {
                    $newGsarr = new GSArray($val);
                    $gsarr->add($newGsarr);
                } else {
                    $gsarr->add($val);
                }
            }
        }
    }

    public function add($value)
    {
        array_push($this->map, $value);
    }

    public function getString($inx)
    {
        $obj = $this->map[$inx];
        if ($obj === null)
            return null;
        else
            return strval($obj);
    }

    public function getBool($inx)
    {
        $obj = $this->map[$inx];
        if ($obj === null)
            throw new Exception(GSArray::NO_INDEX_EX + $inx);

        if (is_bool($obj)) {
            return (Boolean)$obj;
        } else {
            $val = strtolower(strval($obj));
            return $val == "true" || $val == "1";
        }
    }

    public function getInt($inx)
    {

        $obj = $this->map[$inx];
        if ($obj === null)
            throw new Exception(GSArray::NO_INDEX_EX + $inx);

        if (is_int($obj)) {
            return (int)$obj;
        } else {
            return intval($this->getString($inx));
        }
    }

    public function getLong($inx)
    {
        $obj = $this->map[$inx];
        if ($obj === null)
            throw new Exception(GSArray::NO_INDEX_EX + $inx);

        if (is_float($obj)) {
            return (float)$obj;
        } else {
            return floatval($this->getString($inx));
        }
    }

    public function getDouble($inx)
    {
        $obj = $this->map[$inx];
        if ($obj === null)
            throw new Exception(GSArray::NO_INDEX_EX + $inx);

        if (is_double($obj)) {
            return (double)$obj;
        } else {
            return doubleval($this->getString($inx));
        }
    }

    public function getObject($inx)
    {
        return $this->map[$inx];
    }

    public function getArray($inx)
    {
        return $this->map[$inx];
    }

    public function length()
    {
        return sizeof($this->map);
    }

    public function __toString()
    {
        return $this->toJsonString();
    }

    public function toString()
    {
        return $this->toJsonString();
    }

    public function toJsonString()
    {
        try {
            return json_encode($this->serialize());
        } catch (Exception $e) {
            return null;
        }
    }

    public function serialize()
    {
        $arr = Array();
        if (empty($this->map)) return $arr;

        $arr = GSArray::serializeGSArray($this);

        return $arr;
    }

    public static function serializeGSArray($gsarr)
    {
        $arr = Array();
        for ($i = 0; $i < $gsarr->length(); $i++) {
            $val = $gsarr->getObject($i);
            $val = GSObject::serializeValue($val);
            array_push($arr, $val);
        }
        return $arr;
    }
}


class SigUtils
{
    public static function validateUserSignature($UID, $timestamp, $secret, $signature)
    {
        $now = time();
        if (abs($now - $timestamp) > 180) {
            return false;
        }

        $baseString = $timestamp . "_" . $UID;
        $expectedSig = self::calcSignature($baseString, $secret);
        return $expectedSig == $signature;
    }

    public static function validateFriendSignature($UID, $timestamp, $friendUID, $secret, $signature)
    {
        $now = time();
        if (abs($now - $timestamp) > 180) {
            return false;
        }

        $baseString = $timestamp . "_" . $friendUID . "_" . $UID;
        $expectedSig = self::calcSignature($baseString, $secret);
        return $expectedSig == $signature;
    }

    static function currentTimeMillis()
    {
        // get utc time in ms
        list($msecs, $uts) = explode(' ', microtime());
        return floor(($uts + $msecs) * 1000);
    }

    public static function getDynamicSessionSignature($glt_cookie, $timeoutInSeconds, $secret)
    {
        // cookie format:
        // <expiration time in unix time format>_BASE64(HMACSHA1(secret key, <login token>_<expiration time in unix time format>))
        $expirationTimeUnixMS = (SigUtils::currentTimeMillis() / 1000) + $timeoutInSeconds;
        $expirationTimeUnix = (string)floor($expirationTimeUnixMS);
        $unsignedExpString = $glt_cookie . "_" . $expirationTimeUnix;
        $signedExpString = SigUtils::calcSignature($unsignedExpString, $secret); // sign the base string using the secret key

        $ret = $expirationTimeUnix . '_' . $signedExpString;   // define the cookie value

        return $ret;
    }

    static function calcSignature($baseString, $key)
    {
        $baseString = utf8_encode($baseString);
        $rawHmac = hash_hmac("sha1", utf8_encode($baseString), base64_decode($key), true);
        $signature = base64_encode($rawHmac);
        return $signature;
    }
}

?>
