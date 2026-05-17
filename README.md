🔧 Mini Compilador de Lenguaje tipo C con Flex y Bison
Proyecto desarrollado para el curso de Compiladores y Teoría de Lenguajes.
Este es un compilador pequeño escrito en C usando las herramientas Flex y Bison que realiza análisis léxico, análisis sintáctico y genera código de tres direcciones (3AC) a partir de un código fuente similar a C.

📌 ¿De qué trata el proyecto?
El compilador reconoce un lenguaje propio con las siguientes características:

Variables de tipo entero (int)
Palabras reservadas: if, else, while, main, print
Operadores aritméticos: +, -, *, /
Operadores lógicos: >, <, >=, <=
Bloques de código entre {}
Condiciones entre ()
Instrucciones terminadas con ;
Comentarios con //


⚙️ Fases del compilador
1️⃣ Análisis Léxico (Flex)
El archivo lexer.fl define las reglas para reconocer los tokens del lenguaje como palabras reservadas, identificadores, números y operadores.
2️⃣ Análisis Sintáctico (Bison)
El archivo syntax.y define la gramática del lenguaje y verifica que el código fuente cumpla con las reglas sintácticas.
3️⃣ Generación de Código (3AC)
El compilador traduce el código fuente a código de tres direcciones, que es una representación intermedia del programa similar al código ensamblador.

📁 Estructura del proyecto
Versione 1/
├── lexer.fl        # Analizador léxico (Flex)
├── syntax.y        # Analizador sintáctico (Bison)
├── list.h          # Librería para tabla de símbolos
├── uthash.h        # Librería para tabla hash
├── makefile        # Archivo de compilación
└── Esempi/         # Ejemplos de entrada y salida
    ├── input1
    ├── input2
    ├── input3
    ├── input4
    ├── output1
    ├── output2
    ├── output3
    └── output4

🚀 ¿Cómo ejecutarlo?
Requisitos

Linux o GitHub Codespaces
flex
bison
gcc

Pasos
1. Clonar el repositorio:
bashgit clone https://github.com/TU_USUARIO/TU_REPOSITORIO.git
cd "Versione 1"
2. Instalar dependencias:
bashsudo apt-get update && sudo apt-get install flex bison -y
3. Compilar:
bashbison -d syntax.y
flex -o lex.yy.c lexer.fl
cp syntax.tab.h parser.h
gcc syntax.tab.c lex.yy.c -o compiler -lfl
4. Ejecutar con los ejemplos:
bash./compiler < Esempi/input1
./compiler < Esempi/input2
./compiler < Esempi/input3
./compiler < Esempi/input4

📝 Ejemplo de entrada
cmain () {
    int a;
    int b = 0;
    int c = 10;
    if(c>5) {
        a = 0;
        while(a<c) {
            a = a + 1;
        }
        b = 7;
    } else {
        if(c>=10) {
            a = 12;
        }
    }
    print(a);
    print(b);
    print(c);
}
📤 Ejemplo de salida (Código 3AC)
list = insertElement(list);
t0 = 10;
setVarList("c", t0, list);
t1 = getVarList("c", list);
t2 = 5;
t3 = t1 > t2;
if (t3) goto L0;
goto L1;
L0:
...
printf("%s: %d\n", "a", getVarList("a", list));
printf("%s: %d\n", "b", getVarList("b", list));
printf("%s: %d\n", "c", getVarList("c", list));

🛠️ Herramientas utilizadas
HerramientaUsoFlexGenerador de analizadores léxicosBisonGenerador de analizadores sintácticosCLenguaje de implementaciónGCCCompilador de C