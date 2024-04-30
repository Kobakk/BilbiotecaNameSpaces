<?php ob_start(); ?>
<?php if(isset($errorNoPrestamos)): ?>
  <p><?=$errorNoPrestamos?></p>
<?php elseif(isset($errorBd) || isset($errorDesconocido)): $error = $errorBd??$errorDesconocido; ?>
  <p><?=$error?></p>
<?php else: ?>
  <h1>Selecciona los libros que deseas devolver</h1>
  <form action="" method="post">
    <?php foreach ($librosPrestados as $key => $infLibro): ?>
      <p>
        <label><?= $infLibro['titulo']?> 
          <input type="checkbox" name="aDevolver[<?=$infLibro['codigo']?>]" value="<?=$infLibro['idLibroPrestado']?>">
        </label>
      </p>
    <?php endforeach;?>
    <input type="submit" value="Devolver" name="ok">
  </form>
<?php endif;?>


<?php $contenido = ob_get_clean();
  include 'base.inc'; ?>