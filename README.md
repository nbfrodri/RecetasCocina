# RecetasCocina

Aplicación de consola en C++ (Windows) para gestionar y mostrar recetas e ingredientes a partir de ficheros de texto.

## Descripción
Programa que lee recetas y sus ingredientes desde `recetas.txt` y las instrucciones desde `instrucciones.csv`. Permite:
- Crear (pendiente) y mostrar recetas.
- Listar todos los ingredientes.
- Filtrar recetas por ingredientes seleccionados.

Código principal: `main.cpp`. Lógica y funciones relacionadas: `food.cpp` / `food.h`.

## Ejecutar
- El programa busca por defecto los ficheros en la ruta definida en `main.cpp`:
  `P:/EspacioRodrigo/Docs/RecetasCocina/files`
  Si es necesario, editar la variable `dir` en `main.cpp` para apuntar al directorio con los ficheros `recetas.txt` e `instrucciones.csv`.
- Ejecutar desde Visual Studio (__Debug > Start Debugging__ o __Debug > Start Without Debugging__) o lanzar el ejecutable generado.

## Formato de los ficheros de datos

1. recetas.txt
- Cada línea representa una receta.
- Formato (separado por espacios): `<NombreReceta> <Ingrediente1> <Cantidad1> <Ingrediente2> <Cantidad2> ...`
- Los espacios en nombres se codifican con `_` (serán convertidos a espacio en la lectura).
- Ejemplo:
  Tarta_de_manzana manzana 3 harina 200 azucar 100
  En el programa se mostrará: "Tarta de manzana: manzana (3) | harina (200) | azucar (100) |"

2. instrucciones.csv
- CSV con campos separados por `;`. La primera columna es el nombre de la receta (con `_` para espacios); la segunda columna contiene las instrucciones.
- Ejemplo:
  Tarta_de_manzana;Precalentar el horno a 180°C. Mezclar ingredientes. Hornear 45 minutos;

## Uso (flujo principal)
- Al iniciar aparece un menú con opciones numeradas (1–6).
- Al elegir mostrar/filtrar recetas, el programa:
  - Lee y ordena datos.
  - Asigna IDs a recetas e ingredientes.
  - Solicita selección mediante números (IDs).
  - Muestra resultado en consola.

## Notas y limitaciones
- Funcionalidad "Crear receta" (opción 1) está vacía en `main.cpp`.
- El filtrado por ingredientes añade recetas que contienen al menos uno de los ingredientes seleccionados (lógica en `FiltrarRecetasPorIngrediente`).
- El parsing asume formatos estrictos; entradas mal formadas pueden producir errores o lecturas incompletas.
- El programa gestiona memoria manualmente (nuevos `new` en vectores de punteros). Considerar migrar a contenedores con objetos o smart pointers (`std::unique_ptr`) para evitar fugas.

## Mejoras sugeridas
- Implementar opción "Crear receta".
- Mejorar robustez del parser y mensajes de error.

---
Proyecto creado para aprendizaje personal sobre lectura de ficheros y filtrados.
