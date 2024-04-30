<?php

namespace MiniBiblioteca\App\Repository;

use MiniBiblioteca\Core\ConexionBd;

class GestionBdRepositorio
{
  public function getLibros(): array
  {
    $sql = 'SELECT codigo, titulo, autor, genero, prestado
            FROM libro';

    //require_once __DIR__ . '/../../core/ConexionBd.inc';
    try {
      $con = (new ConexionBd())->getConexion();
      $snt = $con->prepare($sql);
      $snt->execute();
      while ($fila = $snt->fetch(\PDO::FETCH_ASSOC)) {
        //$libros[$fila['codigo']]['título']=$fila['titulo'];
        //$libros[$fila['codigo']]['autor']=$fila['autor'];
        //$libros[$fila['codigo']]['género']=$fila['genero'];
        //$libros[$fila['codigo']]['prestado']=$fila['prestado'];
        $libros[$fila['codigo']] = ['título' => $fila['titulo'], 'autor' => $fila['autor'], 'género' => $fila['genero'], 'prestado' => $fila['prestado']];

      }
      return $libros;
    } catch (\PDOException $ex) {
      throw $ex;
    } finally {
      if (isset($snt))
        unset($snt);
      if (isset($con))
        unset($con);
    }

  }

  public function getSocios(): array
  {
    $sql = 'SELECT idSocio, eCorreo, pwd
            FROM socio';

    //require_once __DIR__ . '/../../core/ConexionBd.inc';
    try {
      $con = (new ConexionBd())->getConexion();
      $snt = $con->prepare($sql);
      $snt->execute();
      while ($fila = $snt->fetch(\PDO::FETCH_ASSOC)) {
        $socios[$fila['idSocio']] = ['eCorreo' => $fila['eCorreo'], 'pwd' => $fila['pwd']];
      }
      return $socios;
    } catch (\PDOException $ex) {
      throw $ex;
    } finally {
      if (isset($snt))
        unset($snt);
      if (isset($con))
        unset($con);
    }

  }

  public function getLibrosPrestados(): array
  {
    $sql = 'SELECT idLibroPrestado, codigo as código, eCorreo
            FROM libroPrestado';

    //require_once __DIR__ . '/../../core/ConexionBd.inc';
    try {
      $con = (new ConexionBd())->getConexion();
      $snt = $con->prepare($sql);
      $snt->execute();
      while ($fila = $snt->fetch(\PDO::FETCH_ASSOC)) {
        $libroPrestado[$fila['idLibroPrestado']][] = $fila['código'];
        $libroPrestado[$fila['idLibroPrestado']][] = $fila['eCorreo'];

        //$libroPrestado[$fila['idLibroPrestado']]=
        //  [0=>$fila['código'], 1=>$fila['eCorreo']];
      }
      return $libroPrestado;
    } catch (\PDOException $ex) {
      throw $ex;
    } finally {
      if (isset($snt))
        unset($snt);
      if (isset($con))
        unset($con);
    }
  }

  public function getSocioByECorreo(string $eCorreo): array
  {
    $sql = 'SELECT idSocio, eCorreo, pwd
            FROM socio
           WHERE eCorreo = :eCorreo';
    //require_once __DIR__ . '/../../core/ConexionBd.inc';
    try {
      $con = (new ConexionBd())->getConexion();
      $snt = $con->prepare($sql);
      $snt->bindValue(':eCorreo', $eCorreo);
      $snt->execute();
      $fila = $snt->fetch(\PDO::FETCH_ASSOC);
      if ($fila === false) {
        throw new \Exception('No hay socios con ese eCorreo', 100);
      } else {
        return $fila;
      }
    } catch (\PDOException $ex) {
      throw $ex;
    } finally {
      if (isset($snt))
        unset($snt);
      if (isset($con))
        unset($con);
    }
  }

  public function getLibrosPrestadoByECorreo(string $eCorreo)
  {
    $sql = 'SELECT lp.idLibroPrestado, l.codigo, l.titulo, lp.eCorreo
              FROM libroPrestado as lp INNER JOIN libro as l
                ON lp.codigo = l.codigo
             WHERE lp.eCorreo = :eCorreo';

    try {
      $con = (new ConexionBd())->getConexion();
      $snt = $con->prepare($sql);
      $snt->bindValue(':eCorreo', $eCorreo);
      $snt->execute();
      $filas = $snt->fetchAll(\PDO::FETCH_ASSOC);
      if (empty($filas)) {
        throw new \Exception('El socio no tiene actualmente libros en préstamo', 110);
      } else {
        return $filas;
      }
    } catch (\PDOException $ex) {
      throw $ex;
    } finally {
      if (isset($snt))
        unset($snt);
      if (isset($con))
        unset($con);
    }

  }

  public function devuelveLibros(array $librosADevolver, string $eCorreo)
  {
    $sql1 = "UPDATE libro
                SET prestado = 'FALSE'
              WHERE codigo = :codigo
                AND prestado = 'TRUE'";
    $sql2 = 'DELETE FROM libroPrestado
              WHERE idLibroPrestado = :idLibro
                AND codigo = :codigoPrestado
                AND eCorreo = :eCorreo';

    $codigo = '';
    $idLibro = '';
    try {
      $con = (new ConexionBd())->getConexion();
      $con->beginTransaction();
      $snt1 = $con->prepare($sql1);
      $snt1->bindParam(':codigo', $codigo);
      foreach ($librosADevolver as $codigo => $id) {
        if (!$snt1->execute()) {
          $con->rollBack();
          throw new \Exception('No ha sido posible actualizar la columna préstamo de la tabla libro', 120);
        }
      }
      $snt2 = $con->prepare($sql2);
      $snt2->bindParam(':idLibro', $idLibro);
      $snt2->bindParam(':codigoPrestado', $codigo);
      $snt2->bindParam(':eCorreo', $eCorreo);
      foreach ($librosADevolver as $codigo => $id) {
        $idLibro = $id;
        if (!$snt2->execute()) {
          $con->rollBack();
          throw new \Exception('No ha sido eliminar la información de la tabla libroPrestado', 130);
        }
      }
      $con->commit();
    } catch (\PDOException $ex) {
      $con->rollBack();
      throw $ex;
    } finally {
      if (isset($snt1))
        unset($snt1);
      if (isset($snt2))
        unset($snt2);
      if (isset($con))
        unset($con);
    }
  }

  public function getLibrosDisponibles()
  {
    $sql = 'SELECT codigo, titulo AS Título, Autor, genero AS Género
              FROM libro
             WHERE prestado = 0';

    try {
      $con = (new ConexionBd())->getConexion();
      $snt = $con->prepare($sql);
      $snt->execute();
      $filas = $snt->fetchAll(\PDO::FETCH_ASSOC);
      if (empty($filas)) {
        throw new \Exception('Actualmente todos los libros están prestados', 140);
      } else {
        return $filas;
      }
    } catch (\PDOException $ex) {
      throw $ex;
    } finally {
      if (isset($snt))
        unset($snt);
      if (isset($con))
        unset($con);
    }
  }

  public function prestaLibros(array $librosDeseados, string $eCorreo)
  {
    $sql1 = "UPDATE libro
                SET prestado = 'TRUE'
              WHERE codigo = :codigo
                AND prestado = 'FALSE'";
    $sql2 = 'INSERT libroPrestado (codigo, eCorreo)
              VALUES (:codigoPrestado, :eCorreo)';

    $codigo = '';
    try {
      $con = (new ConexionBd())->getConexion();
      $con->beginTransaction();
      $snt1 = $con->prepare($sql1);
      $snt1->bindParam(':codigo', $codigo);
      foreach ($librosDeseados as $codigo => $valor) {
        if (!$snt1->execute()) {
          $con->rollBack();
          throw new \Exception('No ha sido posible tomar el libro prestado, el libro está ya prestado', 150);
        }
      }
      $snt2 = $con->prepare($sql2);
      $snt2->bindParam(':codigoPrestado', $codigo);
      $snt2->bindParam(':eCorreo', $eCorreo);
      foreach ($librosDeseados as $codigo => $id) {
        if (!$snt2->execute()) {
          $con->rollBack();
          throw new \Exception('No ha sido posible registrar el libro como prestado', 160);
        }
      }
      $con->commit();
    } catch (\PDOException $ex) {
      $con->rollBack();
      throw $ex;
    } finally {
      if (isset($snt1))
        unset($snt1);
      if (isset($snt2))
        unset($snt2);
      if (isset($con))
        unset($con);
    }

  }
}