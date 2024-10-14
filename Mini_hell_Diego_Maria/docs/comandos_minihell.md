| Categoría               | Comando/Funcionalidad | Descripción |
|-------------------------|-----------------------|-------------|
| **Comandos Built-in**    | `echo`                | Imprime argumentos en la terminal, con opción de suprimir el salto de línea (`-n`) |
|                         | `cd`                  | Cambia el directorio actual |
|                         | `pwd`                 | Imprime el directorio de trabajo actual |
|                         | `export`              | Añade o modifica variables de entorno |
|                         | `unset`               | Elimina variables de entorno |
|                         | `env`                 | Muestra las variables de entorno |
|                         | `exit`                | Cierra la shell con un estado de salida opcional |
| **Ejecución de comandos externos** | `ls`                   | Lista el contenido de directorios |
|                         | `cat`                 | Muestra el contenido de archivos |
|                         | `grep`                | Busca patrones dentro de archivos |
|                         | `chmod`               | Cambia los permisos de archivos o directorios |
|                         | `cp`                  | Copia archivos o directorios |
|                         | `mv`                  | Mueve o renombra archivos o directorios |
|                         | `rm`                  | Elimina archivos o directorios |
|                         | `mkdir`               | Crea un nuevo directorio |
|                         | `rmdir`               | Elimina un directorio vacío |
|                         | `touch`               | Crea un archivo vacío o actualiza la fecha de modificación |
|                         | `find`                | Busca archivos dentro del sistema de archivos |
|                         | `wc`                  | Cuenta líneas, palabras y caracteres en archivos |
|                         | `ps`                  | Muestra información de los procesos en ejecución |
|                         | `kill`                | Envía señales para controlar procesos |
|                         | `ping`                | Verifica la conectividad de red con otro sistema |
|                         | `wget`                | Descarga archivos desde la web |
|                         | `curl`                | Transfiere datos desde o hacia un servidor |
| **Redirección de entrada/salida** | `>` `>>` `<`         | Redirecciona la salida o entrada estándar de los comandos |
| **Pipes**                | `|`                   | Conecta la salida de un comando con la entrada de otro |
| **Manejo de señales**    | `Ctrl+C`              | Interrumpe la ejecución de un comando |
|                         | `Ctrl+D`              | Finaliza la entrada estándar (end of file) |
|                         | `Ctrl+Z`              | Suspende un proceso en ejecución |
| **Variables de entorno** | `$HOME`               | Directorio home del usuario |
|                         | `$PATH`               | Rutas donde el shell busca los ejecutables |
|                         | `$USER`               | Nombre del usuario actual |
|                         | `$SHELL`              | Tipo de shell en uso |
|                         | `$PWD`                | Directorio actual de trabajo |
|                         | `$OLDPWD`             | Directorio anterior de trabajo |
|                         | `$TERM`               | Tipo de terminal en uso |
|                         | `$?`                  | Estado de salida del último comando ejecutado |
|                         | `$UID`                | ID del usuario actual |
