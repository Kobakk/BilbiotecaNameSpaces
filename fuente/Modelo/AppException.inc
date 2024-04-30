<?php 

namespace MiniBiblioteca\App\Model;
class AppException extends \Exception
{
  private array $errores;

  public function __construct(array $errores, string $message = ""){
    parent::__construct($message);
    $this->errores=$errores;
  }

  public function getErrores(): array
  {
    return $this->errores;
  }
}