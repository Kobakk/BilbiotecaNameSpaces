<?php
namespace MiniBiblioteca\App\Controller;

use MiniBiblioteca\App\Model\Usuario;
use MiniBiblioteca\App\Model\AppException;
use MiniBiblioteca\App\Repository\GestionBdRepositorio;

class GestionLibrosController
{

  public function devolverLibro()
  {
    $objGestBd = new GestionBdRepositorio();
    if (isset($_POST['ok'])) {
      $librosADevolver = $_POST['aDevolver'];
      //die(var_dump($librosADevolver));
      try {
        $objGestBd->devuelveLibros($librosADevolver, $_SESSION['correo']);
        header('Location: index.php');
      } catch (\PDOException $ex) {
        $errorBD = $ex->getMessage();
      } catch (\Exception $ex) {
        if ($ex->getCode() === 120) {
          $errorLibro = $ex->getMessage();
        } elseif ($ex->getCode() === 130) {
          $errorLibroPrestado = $ex->getMessage();
        } else {
          $errorDesconocido = $ex->getMessage();
        }
      }
    } else {
      try {
        $librosPrestados = $objGestBd->getLibrosPrestadoByECorreo($_SESSION['correo']);
      } catch (\PDOException $ex) {
        $errorBd = $ex->getMessage();
      } catch (\Exception $ex) {
        if ($ex->getCode() === 110) {
          $errorNoPrestamos = $ex->getMessage();
        } else {
          $errorDesconocido = $ex->getMessage();
        }
      }
    }

    include __DIR__ . '/../../app/plantillas/devuelveLibros.inc';
  }
  public function tomarLibro()
  {
    $objGestBd = new GestionBdRepositorio();
    if (isset($_POST['ok'])) {
      $librosDeseados =$_POST['cogePrestado'];
      try {
        $objGestBd->prestaLibros($librosDeseados, $_SESSION['correo']);
        header('Location: index.php');
      } catch (\PDOException $ex) {
        die(var_dump($ex->getMessage()));
      } catch (\Exception $ex) {
        if($ex->getCode()==150){
          die(var_dump($ex->getMessage()));
        }elseif($ex->getCode()==160){
          die(var_dump($ex->getMessage()));
        }else{
          die(var_dump($ex->getMessage()));
        }
      }
    } else {
      try {
        $librosDisponibles = $objGestBd->getLibrosDisponibles();
      } catch (\PDOException $ex) {
        //throw $th;
      } catch (\Exception $ex) {
        if ($ex->getCode() == 140) {
          $errorNoHayDisponibles = $ex->getMessage();
        }
      }
    }
    include __DIR__ . '/../../app/plantillas/prestaLibros.inc';
  }
}