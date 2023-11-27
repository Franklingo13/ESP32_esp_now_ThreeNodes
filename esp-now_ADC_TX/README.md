# Proyecto de Ejemplo

(Consulte el archivo README.md en el directorio 'examples' de nivel superior para obtener más información sobre ejemplos.)

Este es el ejemplo más sencillo que se puede compilar. El ejemplo se utiliza con el comando `idf.py create-project`
que copia el proyecto a la ruta especificada por el usuario y establece su nombre. Para obtener más información, consulte la [página de documentación](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)

## Cómo usar el ejemplo
Animamos a los usuarios a utilizar este ejemplo como plantilla para sus nuevos proyectos.
Una forma recomendada es seguir las instrucciones en la [página de documentación](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Contenido del directorio del ejemplo

El proyecto **sample_project** contiene un archivo fuente en lenguaje C [main.c](main/main.c). El archivo se encuentra en la carpeta [main](main).

Los proyectos ESP-IDF se construyen utilizando CMake. La configuración de construcción del proyecto se encuentra en archivos `CMakeLists.txt`
que proporcionan un conjunto de directivas e instrucciones que describen los archivos fuente y los objetivos del proyecto
(ejecutable, biblioteca o ambos).

A continuación, se muestra la estructura de los archivos restantes en la carpeta del proyecto.

├── CMakeLists.txt  
├── main  
│ ├── CMakeLists.txt  
│ └── main.c  
└── README.md  *Este es el archivo que está leyendo actualmente  



Además, el proyecto de ejemplo contiene archivos Makefile y component.mk, que se utilizan para el sistema de construcción heredado basado en Make.
No son necesarios ni se utilizan al compilar con CMake e idf.py.