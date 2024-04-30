<?php

class FileToArrayToFile
{
  public function getArrayFromFile(string $archivo): array
  {
    if(!file_exists($archivo)){
      throw new Exception('No ha sido posible recuperar el array. El archivo '.$archivo.' no existe.');
    }
    $cadena=file_get_contents($archivo);
    $array=unserialize($cadena);
    return $array;
    //return unserialize(file_get_contents($archivo));
  }

  public function saveArrayToFile(string $archivo, array $array): void
  {
    if(file_put_contents($archivo, serialize($array))===false)
      throw new Exception('No ha sido posible salvaguardar el array en el archivo '.$archivo);
  }
}