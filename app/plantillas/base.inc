<!-- Vista común a la mayoría (sino todas) las vistas de la aplicación
     Suele contener la imagen corporativa de la apliación Web
     Concretamente esta página contiene el nombre de la empresa
     "Cadena Tiendas Media" y una barra de hiperenlaces con un enalace a la
     página home, llamado "inicio"
     El nombre del archivo es indiferente: layout, comun, etc.
-->
<!DOCTYPE html>
<html>

<head>
  <title>Biblioteca Cañera</title>
  <meta charset="utf-8">

  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" type="text/css" href='web/css/estilos.css' />
</head>

<body>
  <header>
    <p class="titulo">Biblioteca Cañera</p>
    <p class="subtitulo">Donde cunde el tiempo para la lectura</p>
    <nav>
      <hr>
      <!-- Observa cómo el enlace agrega el valor de la variable GET 'ctl'
             que será analizado en la página index.php, en este caso le da el
             valor 'inicio' para que la vista cambie a la página home de la
             aplicación
         -->
      <a href="index.php?ctl=inicio">Inicio</a> |
      <?php if (empty($_SESSION['correo'])): ?>
        <a href="index.php?ctl=iniSes">Iniciar sesion</a> |
      <?php else: ?>
        <a href="index.php?ctl=usuTomaPrestado">Tomar prestado</a> |
        <a href="index.php?ctl=usuDevuelveLibro">Devolver libro</a> |
        <a href="index.php?ctl=saleSes">Cerrar sesion</a> |
        <span class="saludo">Hola <?= $_SESSION['correo'] ?> </span>
      <?php endif; ?>
      <!-- En general, la mayoría de los enlaces serán a la página index.php
             y una asignación a la variable 'ctl'. El valor de la variable deberá
             ser analizada en la página index.php de cara a encontrar la ruta del
             controlador (y método) que debe procesar la petición
        -->
      <hr>
    </nav>
  </header>
  <div id="contenido">
    <!-- el id css facilita (si se define) la definición del aspecto visual
           de su contenido
           La variable $contenido hará que se muestre la plantilla concreta, el
           contenido concreto, según la solicitud realizada por el usuario
      -->
    <?= $contenido ?>
  </div>
  <footer>
    <hr>
    <p style="text-align:center">- Pie de página -</p>
  </footer>
</body>

</html>