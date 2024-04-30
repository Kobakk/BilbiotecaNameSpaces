<?php ob_start();
$cabeceras = array_keys($librosDisponibles[0]); ?>
<h1>Formulario de selección de libros que deseas tomar prestados</h1>
<form action="" method="post">
<table>
  <thead>
    <tr>
      <?php for ($i = 1, $cant = count($cabeceras); $i < $cant; $i++): ?>
        <th>
          <?= $cabeceras[$i]; ?>
        </th>
      <?php endfor; ?>
      <th>Lo quiero</th>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($librosDisponibles as $value): ?>
    <tr>
    <td><?=$value['Título']?></td>
    <td><?=$value['Autor']?></td>
    <td><?=$value['Género']?></td>
    <td><input type="checkbox" name="cogePrestado[<?=$value['codigo']?>]" ></td>
    </tr>
    <?php endforeach; ?>
  </tbody>
</table>
<input type="submit" name="ok" value="Recoger libros" id="bprestamo">
</form>
<?php $contenido = ob_get_clean();
include 'base.inc'; ?>