![Descripción](https://img.shields.io/badge/Descripción-blue?style=for-the-badge)

- Proyecto **minishell** de 42: recrea un intérprete de órdenes UNIX con funcionalidades básicas de un shell.  
- Permite ejecutar comandos externos, gestionar pipes (`|`), redirecciones (`>`, `<`, `>>`) y heredocs (`<<`).  
- Refuerza conceptos de:
  - Análisis léxico y sintáctico de la línea de comandos.
  - Creación de procesos con `fork()`, ejecución con `execve()`.
  - Gestión de señales (`SIGINT`, `SIGQUIT`) para control de usuario.
  - Implementación de **built‑ins** y gestión de variables de entorno.

![Built‑ins](https://img.shields.io/badge/Built%E2%80%91ins-green?style=for-the-badge)

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`


![Estructura](https://img.shields.io/badge/Estructura-orange?style=for-the-badge)

```text
10.Minishell-main/
├── includes/           
│   └── minishell.h       # Prototipos, structs y constantes
├── srcs/              
│   ├── lexer.c           # Tokenización de la línea
│   ├── parser.c          # Construcción del AST / lista de comandos
│   ├── executor.c        # Ejecución (fork, pipes, redirección)
│   ├── builtins.c        # Implementación de comandos internos
│   ├── signals.c         # Handlers de SIGINT/SIGQUIT
│   ├── utils.c           # Funciones auxiliares (strings, listas)
│   └── …
├── Makefile             # Reglas de compilación y limpieza
└── minishell            # Ejecutable resultado
```

![Compilación](https://img.shields.io/badge/Compilación-blue?style=for-the-badge)

- make

- make all — Compila todas las fuentes y genera minishell.

- make clean — Elimina los objetos intermedios (*.o).

- make fclean — Además de clean, elimina minishell.

- make re — Ejecuta fclean y luego all.

![Uso](https://img.shields.io/badge/Uso-yellow?style=for-the-badge)

 1. Ejecutar en terminal
    
        ./minishell

 2. Escribe comandos como en un shell normal:
    
        Ejemplo: ls -la | grep ".c" > salida.txt
 
- Soporta múltiples pipes y combinaciones de redirección.

- Built‑ins afectan el entorno del propio proceso (e.g. cd, export).

- Para salir, usa exit o pulsa Ctrl+D.

    


![Autores](https://img.shields.io/badge/Autores-red?style=for-the-badge)

- Roberto del Olmo Lima
- Pablo Romero Avila
  
- [![GitHub](https://img.shields.io/badge/GitHub-Profile-informational?style=for-the-badge&logo=github&logoColor=white&color=181717)](https://github.com/legrol)
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/roberto-del-olmo-731746245)
