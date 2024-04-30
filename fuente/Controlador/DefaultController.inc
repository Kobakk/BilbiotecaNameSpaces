<?php
namespace MiniBiblioteca\App\Controller;
use MiniBiblioteca\App\Repository\GestionBdRepositorio;

class DefaultController
{ 
  public function inicio()
  { 
    try
    {
      //include_once __DIR__ . '/../Repositorio/FileToArrayToFile.inc';
      //require_once __DIR__ . '/../Repositorio/GestionBdRepositorio.inc';
      $arrayLibros = (new GestionBdRepositorio())->getLibros();
      //$arrayLibros = (new FileToArrayToFile())->getArrayFromFile(LIBROS_FILE);
      $cabeceraArray = array_keys($arrayLibros[array_key_first($arrayLibros)]);
    } catch(\Exception $ex){
      die($ex->getMessage());
    }
    require __DIR__ . '/../../app/plantillas/inicio.inc';
  }

}
