<?php

namespace MiniBiblioteca\App\Model;

class Usuario
{
  private string $eCorreo;
  private string $pwd;

  public function __construct(string $eCorreo, string $pass)
  {
    $resultado = $this->setECorreo($eCorreo);
    if (is_string($resultado)) {
      $error['eCorreo'] = $resultado;
    }

    if(is_string($resultado=$this->checkPass($pass))){
      $error['pass'] = $resultado;
    }

    if(isset($error)){
      require_once 'AppException.inc';
      throw new AppException($error);
    }
  }

  public function setECorreo(string $eCorreo): string|true
  {
    if (!filter_var($eCorreo, FILTER_VALIDATE_EMAIL)) {
      return 'Formato de eCorreo no válido';
    }
    $this->eCorreo = $eCorreo;
    return true;
  }

  public function setPwd(string $pwd)
  {
    $this->pwd = $pwd;
  }

  public function checkPass(string $pass): string|true
  {
    $expRegPass = '/(?=.*\d)(?=.*[A-Z])(?=.*[a-z])(?=.*[?]).{8,15}/';
    if ((!preg_match($expRegPass, $pass))) {
      return 'Formato de Contraseña no válido';
    }
    return true;
  }

  public function getECorreo(): string
  {
    return $this->eCorreo;
  }

  public function getPwd(): string
  {
    return $this->pwd;
  }
}