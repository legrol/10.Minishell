# Introducción

En el capítulo anterior, cubrimos cómo usar un programa shell utilizando comandos UNIX. El shell es un programa que interactúa con el usuario a través de una terminal o toma la entrada desde un archivo y ejecuta una secuencia de comandos que son enviados al sistema operativo. En este capítulo aprenderás cómo escribir tu propio programa shell.

## Programas Shell

Un programa shell es una aplicación que permite interactuar con la computadora.  
En un shell, el usuario puede ejecutar programas y también redirigir la entrada para que provenga de un archivo y la salida para que vaya a un archivo.   
Además, los programas shell ofrecen características como edición de líneas, historial, autocompletado de archivos, comodines, expansión de variables de entorno y construcciones de programación.  
  
Programas shell más populares en UNIX:

| **Shell**  | **Descripción**                                                                 |
|------------|---------------------------------------------------------------------------------|
| `sh`       | El programa shell original en UNIX.                                             |
| `csh`      | C Shell. Una versión mejorada de `sh`.                                          |
| `tcsh`     | Una versión de `Csh` con edición de líneas.                                     |
| `ksh`      | Korn Shell. El padre de todos los shells avanzados.                             |
| `bash`     | El shell de GNU. Combina lo mejor de todos los programas shell. Actualmente, es el programa shell más común. |

## Partes de un Programa Shell

La implementación de un shell se divide en tres partes: el **Parser**, el **Ejecutor**, y los **Subsistemas del Shell**.

### El Parser

El Parser es el componente de software que lee la línea de comando, como `ls -al`,   
y la organiza en una estructura de datos llamada **Tabla de Comandos**, que almacenará los comandos que se ejecutarán.  

### El Ejecutor

El ejecutor tomará la tabla de comandos generada por el parser y, por cada **SimpleCommand** en el array,   
creará un nuevo proceso. Si es necesario, también creará tuberías para comunicar la salida de un proceso a la entrada del siguiente.   
Además, redirigirá la entrada estándar, salida estándar y error estándar si hay redirecciones.  

La siguiente figura muestra una línea de comando `A | B | C | D`. Si el parser detecta una redirección como `< infile`,  
la entrada del primer **SimpleCommand** (`A`) se redirige desde `infile`. Si hay una redirección de salida como `> outfile,  
la salida del último **SimpleCommand** (`D`) se redirige a `outfile.   
Si hay una redirección a un archivo de errores como `>& errfile`, el `stderr` de todos los procesos **SimpleCommand** se redirigirá a `errfile. 

![Flujo de ejecución](https://github.com/mariagomez96-stack/Mini_hell/blob/main/docs/A%20B%20C%20D.png?raw=true)

### Subsistemas del Shell

Otros subsistemas que completan shell son:

- **Variables de Entorno**: Las expresiones de la forma `${VAR}` se expanden con la variable de entorno correspondiente.  
  Además, el shell debe ser capaz de establecer, expandir e imprimir variables de entorno.  
- **Comodines**: Los argumentos de la forma `a*a` se expanden a todos los archivos que coincidan en el directorio local y en múltiples directorios.  
- **Subshells**: Los argumentos entre `` ` `` (backticks) se ejecutan y la salida se envía como entrada al shell.  

### El Analizador (Parser)

Utilizarás dos herramientas UNIX para implementar el analizador: Lex y Yacc.   
Estas herramientas se utilizan para implementar compiladores, intérpretes y preprocesadores.   

Un analizador se divide en dos partes: un Analizador Léxico o Lexer que toma los caracteres de entrada y los agrupa en palabras llamadas tokens,   
y un Parser que procesa los tokens de acuerdo a una gramática y construye la tabla de comandos.  
Diagrama del Shell con el Lexer, el Parser y los otros componentes.  

![Diagrama](https://github.com/mariagomez96-stack/Mini_hell/blob/main/docs/Diagrama.png)

### Explicación del Diagrama de Shell

Este diagrama ilustra el flujo de procesamiento de una línea de comandos dentro de un shell, desglosando cada componente que interactúa en el proceso: **Lexer**, **Parser**, **Tabla de Comandos**, **Wildcard and Envars**, y el **Executor**.

#### 1. **Lexer (Analizador Léxico)**:
- **Función**: El Lexer es responsable de descomponer la entrada del usuario (la línea de comandos) en unidades más pequeñas llamadas **tokens**.  
- Un token puede ser un comando (`ls`), un argumento (`-al`), un operador (`|`, `>`, `<`), o un archivo (`file.txt`).  
  
  **Ejemplo**:
  - Entrada: 
    ```bash
    ls -al | grep "error" > output.txt
    ```
  - Tokens generados:
    - Comando: `ls`
    - Argumento: `-al`
    - Operador: `|`
    - Comando: `grep`
    - Argumento: `"error"`
    - Redirección: `>`
    - Archivo de salida: `output.txt`

#### 2. **Parser (Analizador Sintáctico)**:
- **Función**: El Parser organiza los tokens generados por el Lexer según las reglas gramaticales de la shell (definidas en `shell.y`),  
- y construye una **Tabla de Comandos**. El Parser también identifica pipes y redirecciones.  

  **Ejemplo**:
  - Para la línea de comandos:
    ```bash
    ls -al | grep "error" > output.txt
    ```
  - El Parser crea una estructura que refleja:
    - Primer comando: `ls -al`
    - Pipe: conecta la salida de `ls` con la entrada de `grep`
    - Segundo comando: `grep "error"`
    - Redirección de salida: `> output.txt`

#### 3. **Tabla de Comandos**:
- **Función**: La **Tabla de Comandos** es una representación estructurada de los comandos y sus conexiones, como pipes y redirecciones,  
- organizada para ser ejecutada por el shell. Esta tabla aún puede ser modificada por comodines o variables de entorno antes de ser ejecutada.

  **Ejemplo**:
  - La Tabla de Comandos del ejemplo anterior sería:
    - Comando 1: `ls -al`
    - Pipe: conecta la salida de `ls -al` con la entrada de `grep`
    - Comando 2: `grep "error"`
    - Redirección de salida: `> output.txt`

#### 4. **Wildcard and Envars (Comodines y Variables de Entorno)**:
- **Función**: Antes de que la **Tabla de Comandos** sea ejecutada, el shell expande los **comodines** y **variables de entorno** presentes en la línea de comandos.
- Los comodines son patrones que coinciden con archivos, mientras que las variables de entorno son sustituidas por sus valores.  
  
  **Ejemplo de Variables de Entorno**:
  - Entrada:
    ```bash
    export HOME_DIR="/home/usuario"
    ls -al $HOME_DIR
    ```
  - El shell expande `$HOME_DIR` a `/home/usuario`, resultando en:
    ```bash
    ls -al /home/usuario
    ```

  **Ejemplo de Comodines**:
  - Entrada:
    ```bash
    grep "error" *.log
    ```
  - El comodín `*.log` se expande a todos los archivos `.log` en el directorio actual, como `system.log` y `app.log`.

#### 5. **Executor**:
- **Función**: El Executor toma la **Tabla de Comandos Final** (con las expansiones de comodines y variables de entorno aplicadas)  
  y ejecuta cada comando, gestionando las conexiones entre ellos (como pipes) y redirigiendo la entrada y salida según sea necesario.  
  
  **Ejemplo Completo**:
  ```bash
  export LOG_DIR="/var/logs"
  grep "error" $LOG_DIR/*.log | tee $LOG_DIR/errors.txt | wc -l

- Paso 1: El Lexer convierte esta línea en tokens.  

- Paso 2: El Parser organiza estos tokens en una Tabla de Comandos.  
- Paso 3: El shell expande $LOG_DIR a /var/logs y *.log a los archivos correspondientes.  
- Paso 4: El Executor ejecuta los comandos en secuencia:  

  - grep "error" /var/logs/*.log: filtra las líneas que contienen "error".  
  -  tee /var/logs/errors.txt: guarda las líneas filtradas en errors.txt y las pasa al siguiente comando.  
  -  wc -l: cuenta cuántas líneas contienen "error" y muestra el resultado.
 
  ### Sintaxis del Comando

El siguiente fragmento describe la estructura de un comando en una shell,  
incluyendo la posibilidad de agregar argumentos, usar pipes, redirigir la entrada y salida, y ejecutar comandos en segundo plano.

```bash
cmd [arg]* [ | cmd [arg]* ]*
[ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]
```

  ### Explicación Paso a Paso

1. **cmd [arg]***

   - **cmd**: Es el comando principal que deseas ejecutar (por ejemplo, `ls`, `grep`, `cat`, etc.).
   - **[arg]***: Los argumentos que puedes pasar al comando. Los corchetes `[]` indican que son opcionales,  
     y el asterisco `*` indica que puede haber cero o más argumentos.

   **Ejemplo**:
   - `ls -al`: Aquí, `ls` es el comando, y `-al` es el argumento.

2. **[ | cmd [arg]* ]***

   - **`|`**: Indica el uso de un **pipe**. Un pipe conecta la salida de un comando con la entrada de otro.
   - **cmd [arg]***: Otro comando que toma la salida del comando anterior como su entrada.
   - **[ ]***: Puedes tener cero o más pipes.

   **Ejemplo**:
   ```bash
   ls -al | grep "txt" | sort
   ```

### [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]*

Esta parte describe las redirecciones de entrada y salida.

- **`> filename`**: Redirige la salida estándar (stdout) a un archivo, sobrescribiéndolo.
- **`< filename`**: Redirige la entrada estándar (stdin) desde un archivo.
- **`>& filename`**: Redirige tanto la salida estándar (stdout) como el error estándar (stderr) a un archivo.
- **`>> filename`**: Redirige la salida estándar a un archivo, añadiéndola al final.
- **`>>& filename`**: Redirige tanto la salida estándar como el error estándar y las añade al archivo.

### Ejemplos:

- `ls -al > salida.txt`: Redirige la salida de `ls` a `salida.txt`.
- `cat < entrada.txt`: Toma la entrada desde `entrada.txt`.
- `ls >& salida.txt`: Redirige tanto la salida como los errores a `salida.txt`.
- `ls >> salida.txt`: Añade la salida de `ls` a `salida.txt`.

### [&]:

- **&**: Si aparece al final de un comando, indica que el comando debe ejecutarse en segundo plano (background).  
  Esto permite que el terminal esté disponible para otros comandos mientras el comando en background sigue ejecutándose.  

    **Ejemplo**:

    ```bash
    ./script.sh &
    ```  
    Este comando ejecuta `script.sh` en segundo plano.

### Ejemplo Completo:

```bash
grep "error" log.txt | sort > sorted.txt &
 ```  
#### Explicación del Comando:

- `grep "error" log.txt`: Filtra las líneas que contienen "error" del archivo `log.txt`.
- `| sort`: La salida del comando anterior se pasa al comando `sort`, que ordena las líneas.
- `> sorted.txt`: La salida de `sort` se redirige al archivo `sorted.txt`, sobrescribiéndolo si ya existe.
- `&`: Todo el proceso se ejecuta en segundo plano, permitiéndote seguir usando la terminal mientras el comando se ejecuta.

