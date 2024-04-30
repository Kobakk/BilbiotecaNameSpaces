<?php ob_start(); ?>
<form action="" method="post">
  <fieldset>
    <legend>Datos de inicio de sesión</legend>
    <label>Usuario/ECorreo: <input type="text" name="eCorreo"></label>
    <?php if(isset($errorECorreo)): ?>
      <p class="error">Formato de eCorreo no correcto</p>
    <?php endif; ?>
    <label>Contraseña: <input type="password" name="pass"></label>
    <?php if(isset($errorContraseña)): ?>
      <p class="error">Formato de contraseña no válido</p>
    <?php endif; ?>
    <?php if(isset($errorDatosIncompletos)): ?>
      <p class="error">Falta el correo o la contraseña</p>
    <?php endif; ?>
    <?php if(isset($errorIniSes)): ?>
      <p class="error">Usuario o contraseña no válidos</p>
    <?php endif; ?>
    <?php if(isset($errorNoExiste)): ?>
      <p class="error">El usuario especificado no está registrado</p>
    <?php endif; ?>
    <?php if(isset($errorBd)): ?>
      <p class="error"><?=$errorBd?></p>
    <?php endif; ?>
   
    
    <input type="submit" value="Ingresar" name="ok">
  </fieldset>
</form>
<?php $contenido = ob_get_clean();
  include 'base.inc'; ?>