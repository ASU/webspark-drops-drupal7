<?php

$result1 = apc_clear_cache();
$result2 = apc_clear_cache('user');
$result3 = apc_clear_cache('opcode');
$infos = apc_cache_info();
$infos['apc_clear_cache'] = $result1;
$infos["apc_clear_cache('user')"] = $result2;
$infos["apc_clear_cache('opcode')"] = $result3;
$infos["success"] = $result1 && $result2 && $result3;
header('Content-type: application/json');
echo json_encode($infos);

