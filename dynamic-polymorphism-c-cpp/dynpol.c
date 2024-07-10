#include <stdio.h>
#include <stdlib.h>

typedef char const* (*PTRFUN)();

char const* dogGreet(void) {
  return "vau!";
}
char const* dogMenu(void) {
  return "kuhanu govedinu";
}
char const* catGreet(void) {
  return "mijau!";
}
char const* catMenu(void) {
  return "konzerviranu tunjevinu";
}

PTRFUN dogFunctions[] = {
    dogGreet,
    dogMenu
};

PTRFUN catFunctions[] = {
    catGreet,
    catMenu
};

struct Animal {
    const char* name;
    PTRFUN* vtable;
};

void animalPrintGreeting(struct Animal* animal) {
    printf("%s greets: %s! \n", animal->name, animal->vtable[0]());
}

void animalPrintMenu(struct Animal* animal) {
    printf("%s loves %s \n", animal->name, animal->vtable[1]());
}

void constructDog(struct Animal* dog, const char* name) {
    dog->name = name;
    dog->vtable = dogFunctions;
}

void constructCat(struct Animal* cat, const char* name) {
    cat->name = name;
    cat->vtable = catFunctions;
}

struct Animal* createDog(const char* name) {
    struct Animal* dog = malloc(sizeof(struct Animal));
    if (dog != NULL) {
        constructDog(dog, name);
    }
    return dog;    
};

struct Animal* createCat(const char* name) {
    struct Animal* cat = malloc(sizeof(struct Animal));
    if (cat != NULL) {
        constructCat(cat, name);
    }
    return cat;    
};

void testAnimals(void){
  struct Animal* p1=createDog("Hamlet");
  struct Animal* p2=createCat("Ofelija");
  struct Animal* p3=createDog("Polonije");

  animalPrintGreeting(p1);
  animalPrintGreeting(p2);
  animalPrintGreeting(p3);

  animalPrintMenu(p1);
  animalPrintMenu(p2);
  animalPrintMenu(p3);

  free(p1); free(p2); free(p3);
}

void stackVsHeap() {
    struct Animal stackDog;
    constructDog(&stackDog, "stackDog");

    struct Animal* heapDog = createDog("heapDog");

    printf("I am a stack dog: %s \n", stackDog.name);
    printf("I am a heap dog: %s \n", heapDog->name);

    free(heapDog);
}

int main() {
    stackVsHeap();
    return 0;
}
