<?php
namespace MiniBiblioteca\App\Controller;

use MiniBiblioteca\App\Model\Usuario;
use MiniBiblioteca\App\Model\AppException;
use MiniBiblioteca\App\Repository\GestionBdRepositorio;

class SessionController
{
  public function iniSes()
  {
    if (isset($_POST['ok'])) {
      require_once __DIR__ . '/../../app/utilidades/sanea.inc';
      $eCorreo = sanea($_POST['eCorreo']);
      $pass = sanea($_POST['pass']);
      if (empty($eCorreo) || empty($pass)) {
        $errorDatosIncompletos = true;
      } else {
        require_once __DIR__ . '/../Modelo/Usuario.inc';
        require_once __DIR__ . '/../Modelo/AppException.inc';
        try {
          $objUsuario = new Usuario($eCorreo, $pass);
          require_once __DIR__ . '/../Repositorio/GestionBdRepositorio.inc';
          try {
            $usuario = (new GestionBdRepositorio())->getSocioByECorreo($eCorreo);
            if (password_verify($pass, $usuario['pwd'])) {
              $objUsuario->setPwd($usuario['pwd']);
              $_SESSION['correo'] = $objUsuario->getECorreo();
              $_SESSION['usuario'] = $objUsuario;
              header('Location: index.php');
              exit();
            }
            $errorIniSes = true;
          } catch (\PDOException $ex) {
            $errorBd = $ex->getMessage();
          } catch (\Exception $ex) {
            if ($ex->getCode() === 100)
              $errorNoExiste = $ex->getMessage();
          }
        } catch (AppException $ex) {
          $errores = $ex->getErrores();
          if (isset($errores['eCorreo'])) {
            $errorECorreo = $errores['eCorreo'];
          }
          if (isset($errores['pass'])) {
            $errorContraseña = $errores['pass'];
          }
        }
      }
    }

    require __DIR__ . '/../../app/plantillas/iniSes.inc';

  }

  public function saleSes()
  {
    unset($_SESSION['correo']);
    session_destroy();
    header('Location: index.php');
    exit();
  }
}