<?php

/**
 * Predis client specific implementation.
 */
class Redis_Client_Predis implements Redis_Client_FactoryInterface {

  /**
   * Circular depedency breaker.
   */
  static protected $autoloaderRegistered = false;

  /**
   * If the first cache get operation happens after the core autoloader has
   * been registered to PHP, during our autoloader registration we will
   * trigger it when calling class_exists(): core autoloader will then run
   * cache_get() during autoloading but sadly this will run our autoloader
   * registration once again. The second time we are called the circular
   * dependency breaker will act and we will do nothing, ending up in a
   * class instanciation attempt while the autoloader is still not loaded.
   */
  static protected $stupidCoreWorkaround = 0;

  /**
   * Define Predis base path if not already set, and if we need to set the
   * autoloader by ourself. This will ensure no crash. Best way would have
   * been that Drupal ships a PSR-0 autoloader, in which we could manually
   * add our library path.
   * 
   * We cannot do that in the file header, PHP class_exists() function wont
   * see classes being loaded during the autoloading because this file is
   * loaded by another autoloader: attempting the class_exists() during a
   * pending autoloading would cause PHP to crash and ignore the rest of the
   * file silentely (WTF!?). By delaying this at the getClient() call we
   * ensure we are not in the class loading process anymore.
   */
  public static function setPredisAutoload() {

    if (self::$autoloaderRegistered) {
      return;
    }

    self::$stupidCoreWorkaround++;

    // If you attempt to set Drupal's bin cache_bootstrap using Redis, you
    // will experience an infinite loop (breaking by itself the second time
    // it passes by): the following call will wake up autoloaders (and we
    // want that to work since user may have set its own autoloader) but
    // will wake up Drupal's one too, and because Drupal core caches its
    // file map, this will trigger this method to be called a second time
    // and boom! Adios bye bye. That's why this will be called early in the
    // 'redis.autoload.inc' file instead.
    if (1 < self::$stupidCoreWorkaround || !class_exists('Predis\Client')) {

      if (!defined('PREDIS_BASE_PATH')) {
        $search = DRUPAL_ROOT . '/sites/all/libraries/predis';
        define('PREDIS_BASE_PATH', $search);
      } else {
        $search = PREDIS_BASE_PATH;
      }

      if (is_dir($search . '/src')) { // Predis v1.x
        define('PREDIS_VERSION_MAJOR', 1);
      } else if (is_dir($search . '/lib')) { // Predis v0.x
        define('PREDIS_VERSION_MAJOR', 0);
      } else {
        throw new Exception("PREDIS_BASE_PATH constant must be set, Predis library must live in sites/all/libraries/predis.");
      }

      // Register a simple autoloader for Predis library. Since the Predis
      // library is PHP 5.3 only, we can afford doing closures safely.
      switch (PREDIS_VERSION_MAJOR) {

        case 0:
          $autoload = function($classname) { // PSR-0 autoloader.
            if (0 === strpos($classname, 'Predis\\')) {
              $filename = PREDIS_BASE_PATH . '/lib/' . str_replace('\\', '/', $classname) . '.php';
              return (bool)require_once $filename;
            }
            return false;
          };
          break;

        case 1:
          // Register a simple autoloader for Predis library. Since the Predis
          // library is PHP 5.3 only, we can afford doing closures safely.
          $autoload = function($classname) { // PSR-4 autoloader
            if (0 === strpos($classname, 'Predis\\')) {
              $filename = PREDIS_BASE_PATH . '/src/' . str_replace('\\', '/', substr($classname, 7)) . '.php';
              return (bool)require_once $filename;
            }
            return false;
          };
          break;
      }

      if ($autoload) {
        spl_autoload_register($autoload);
      }

      // Same reason why we have the stupid core workaround, if this happens
      // during a second autoload call, PHP won't call the newly registered
      // autoloader function, so just load the file.
      if (1 < self::$stupidCoreWorkaround) {
        call_user_func($autoload, 'Predis\Client');
      }
    }

    self::$autoloaderRegistered = true;
  }

  public function getClient($options = array()) {

    self::setPredisAutoload();

    if (!empty($options['socket'])) {
      $options['scheme'] = 'unix';
      $options['path'] = $options['socket'];
    }

    foreach ($options as $key => $value) {
      if (!isset($value)) {
        unset($options[$key]);
      }
    }

    // I'm not sure why but the error handler is driven crazy if timezone
    // is not set at this point.
    // Hopefully Drupal will restore the right one this once the current
    // account has logged in.
    date_default_timezone_set(@date_default_timezone_get());

    $client = new \Predis\Client($options);

    if (isset($options['base']) && 0 !== $options['base']) {
        $client->select((int)$options['base']);
    }

    return $client;
  }

  public function getName() {
    return 'Predis';
  }
}
