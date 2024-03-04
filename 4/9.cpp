/*
Во програмскиот јазик C да се креира структура Movie за опишување на филм во рамките на една стриминг платформа. Структурата за филм треба да ги содржи следниве полиња: (5 поени)

Име (низа од 100 знаци)

Рејтинг (реален број)

Жанр (низа од 40 знаци)

Да се креира структура StreamingService, што ги содржи следниве полиња: (5 поени)

Име на стриминг платформата (низа од 50 знаци)

Низа од достапни филмови (низа од максимум 30 елементи од структурата Movie)

Број на елементи во низата (цел број)

Да се креира глобална функција print за печатење на информациите за дадена стриминг платформа во следниот формат: (10 поени)

[Ime na streaming platformata]

[ImeFilm1] [Rejting1]

[ImeFilm2] [Rejting2]

[ImeFilm3] [Rejting3]

...

Да се креира функција showBestStreamningService, што прима низа од променливи од типот StreamingService, и променлива genre. Оваа функција треба да го испечати името на стриминг платформата која нуди најмногу филмови кои се од даден жанр (во зависност од пратената променлива genre). Ако има повеќе такви стриминг платформи со максимален број на филмови од пратениот жанр, се печати првата.(15 поени)

Да се дополни функцијата main (5 поени).
 */
#include <stdio.h>
#include <string.h>

typedef struct Movie{
    char name[100];
    float rating;
    char genre[40];
} Movie;

typedef struct StreamingService{
    char name[50];
    Movie movies[30];
    int num_movies;
} StreamingService;

void print(StreamingService service) {
    printf("%s\n", service.name);
    for (int i = 0; i < service.num_movies; i++) {
        printf("%s %.1f\n", service.movies[i].name, service.movies[i].rating);
    }
}

void showBestStreamingService(StreamingService services[], int num_services, char genre[]) {
    int max_count = 0;
    int best_index = -1;

    for (int i = 0; i < num_services; i++) {
        int count = 0;
        for (int j = 0; j < services[i].num_movies; j++) {
            if (strcmp(services[i].movies[j].genre, genre) == 0) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            best_index = i;
        }
    }

    if (best_index != -1) {
        printf("Best streaming service is: %s\n", services[best_index].name);
    } else {
        printf("No service has movies of the given genre.\n");
    }
}

int main() {
    StreamingService services[100];
    int num_services;
    scanf("%d", &num_services);

    for (int i = 0; i < num_services; i++) {
        scanf("%s %d", services[i].name, &services[i].num_movies);
        for (int j = 0; j < services[i].num_movies; j++) {
            scanf("%s %f %s", services[i].movies[j].name, &services[i].movies[j].rating, services[i].movies[j].genre);
        }
        print(services[i]);
    }

    char genre[40];
    scanf("%s", genre);

    showBestStreamingService(services, num_services, genre);

    return 0;
}
