<?php
//index.php
session_start();
error_reporting(E_ALL);
if(!isset($_SESSION['correo'])){
  $_SESSION['correo']="";
}

function getFuente(string $clase)
{
  if(strpos($clase,'MiniBiblioteca\App' )===0){
    if(strpos($clase,'MiniBiblioteca\App\Controller')===0){
      $clase = str_replace('MiniBiblioteca\App\Controller','',$clase);
      $clase = str_replace('\\','/',$clase);
      //die(var_dump($clase));
      require_once __DIR__ . '/fuente/Controlador'.$clase.'.inc';
    }elseif(strpos($clase,'MiniBiblioteca\App\Model')===0){
      $clase = str_replace('MiniBiblioteca\App\Model','',$clase);
      $clase = str_replace('\\','/',$clase);
      require_once __DIR__ . '/fuente/Modelo'.$clase.'.inc';
    }elseif(strpos($clase, 'MiniBiblioteca\App\Repository')===0){
      $clase = str_replace('MiniBiblioteca\App\Repository','',$clase);
      $clase = str_replace('\\','/',$clase);
      require_once __DIR__ . '/fuente/Repositorio'.$clase.'.inc';
    }
  }
}

function getCore(string $clase)
{
  if(strpos($clase, 'MiniBiblioteca\Core')===0){
    $clase = str_replace('MiniBiblioteca','',$clase);
    $clase = str_replace('\\','/',$clase);
    require_once __DIR__ . $clase.'.inc';
  }
}

spl_autoload_register('getCore');
spl_autoload_register('getFuente');

//require_once __DIR__ . '/fuente/Controlador/DefaultController.inc'; /*controladores */
//require_once __DIR__ . '/fuente/Controlador/SessionController.inc'; /*controladores */
//require_once __DIR__ . '/fuente/Controlador/GestionLibrosController.inc';
require_once __DIR__ . '/app/conf/rutas.inc'; /*Ubicación del archivo de rutas*/

define('LIBROS_FILE', __DIR__.'/fuente/Repositorio/libros.txt');
define('LIBROS_PRESTADOS_FILE', __DIR__.'/fuente/Repositorio/librosPrestados.txt');
define('SOCIOS_FILE', __DIR__.'/fuente/Repositorio/socios.txt');
//echo LIBROS_FILE;

// Análisis de la ruta
if (isset($_GET['ctl'])){
  if (isset($mapeoRutas[$_GET['ctl']])){
    $ruta = $_GET['ctl'];
  } else {
    header('Status: 404 Not Found');
    echo '<html><body><h1>Error 404: No existe la ruta <i>' .
          $_GET['ctl'] .
          '</i></p></body></html>';
    exit;
  }
} else {
  $ruta = 'inicio';
}

$controlador = $mapeoRutas[$ruta];
// Ejecución del controlador asociado a la ruta

if (method_exists($controlador['controller'],$controlador['action'])){
  call_user_func(array(new $controlador['controller'], $controlador['action']));
} else {
  header('Status: 404 Not Found');
  echo '<html><body><h1>Error 404: El controlador <i>' .
       $controlador['controller'] .
       '->' . $controlador['action'] .
       '</i> no existe</h1></body></html>';
}
