<?php
/* Ejemplo de plantilla que se mostrará dentro de la plantilla principal
  ob_start() activa el almacenamiento en buffer de la página. Mientras se
             almacena en el buffer no se produce salida alguna hacia el
             navegador del cliente
  luego viene el código html y/o php que especifica lo que debe aparecer en
     el cliente web
  ob_get_clean() obtiene el contenido del buffer (que se pasa a la variable
             $contenido) y elimina el contenido del buffer
  Por último se incluye la página que muestra la imagen común de la aplicación
    (en este caso base.php) la cual contiene una referencia a la variable
    $contenido que provocará que se muestre la salida del buffer dentro dicha
    página "base.php"
*/
 ?>
<?php ob_start(); ?>
<h1>Estos son los libros que puedes consultar en nuestra Biblioteca</h1>
<table>
  <thead>
    <tr>
      <?php foreach ($cabeceraArray as $value): ?>
        <th><?=ucfirst($value)?></th>
      <?php endforeach; ?>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($arrayLibros as $codigo => ['título'=>$titulo,'autor'=>$autor,'género'=>$genero, 'prestado'=>$prestado]): ?>
      <tr>
        <td><?=$titulo?></td>
        <td><?=$autor?></td>
        <td><?=$genero?></td>
        <td><?=!$prestado?'Disponible':'Prestado'?></td>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
 <?php $contenido = ob_get_clean() ?>

 <?php include 'base.inc' ?>
