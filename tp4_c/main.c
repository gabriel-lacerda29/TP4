#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_SIZE 4096
#define MAX_FIELD_SIZE 1024
#define MAX_GAMES 2000
#define MAX_INPUT_SIZE 256

// Definição da struct Game
typedef struct {
    int appID;
    char* name;
    char* releaseDate;
    int estimatedOwners;
    float price;
    char** supportedLanguages;
    int supportedLanguagesCount;
    int metacriticScore;
    float userScore;
    int achievements;
    char** publishers;
    int publishersCount;
    char** developers;
    int developersCount;
    char** categories;
    int categoriesCount;
    char** genres;
    int genresCount;
    char** tags;
    int tagsCount;
} Game;

// Protótipos das funções
char** formatarArrayString(const char* entrada, int tipo, int* count);
char** removerEspacosIniciais(char** array, int size);
bool compare(const char* str1, const char* str2);
void formatarArrayParaPrint(char** array, int count, char* resultado, int tipo);
void freeGame(Game* game);

// Setters
void setAppID(Game* game, const char* appID) {
    game->appID = atoi(appID);
}

void setName(Game* game, const char* name) {
    if (game->name) free(game->name);
    game->name = strdup(name);
}

void setReleaseDate(Game* game, const char* releaseDate) {
    char mesStr[4] = {0};
    char diaStr[3] = {0};
    char anoStr[5] = {0};
    char mesNum[3] = {0};
    char resp[11];

    if (strlen(releaseDate) < 8) {
        if (game->releaseDate) free(game->releaseDate);
        game->releaseDate = strdup("01/01/2000");
        return;
    }

    strncpy(mesStr, releaseDate, 3);
    mesStr[3] = '\0';

    if (releaseDate[5] == ',') {
        diaStr[0] = '0';
        diaStr[1] = releaseDate[4];
        strncpy(anoStr, releaseDate + 7, 4);
        anoStr[4] = '\0';
    } else {
        strncpy(diaStr, releaseDate + 4, 2);
        diaStr[2] = '\0';
        strncpy(anoStr, releaseDate + 8, 4);
        anoStr[4] = '\0';
    }

    const char* meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const char* mesesNum[] = {"01", "02", "03", "04", "05", "06", 
                             "07", "08", "09", "10", "11", "12"};
    
    strcpy(mesNum, "01");
    for (int i = 0; i < 12; i++) {
        if (strcmp(mesStr, meses[i]) == 0) {
            strcpy(mesNum, mesesNum[i]);
            break;
        }
    }

    sprintf(resp, "%s/%s/%s", diaStr, mesNum, anoStr);
    if (game->releaseDate) free(game->releaseDate);
    game->releaseDate = strdup(resp);
}

void setEstimatedOwners(Game* game, const char* estimatedOwners) {
    char aux[MAX_FIELD_SIZE] = {0};
    int j = 0;
    for (int i = 0; i < (int)strlen(estimatedOwners); i++) {
        if (isdigit(estimatedOwners[i])) {
            aux[j++] = estimatedOwners[i];
        }
    }
    aux[j] = '\0';
    game->estimatedOwners = atoi(aux);
}

void setPrice(Game* game, const char* price) {
    if (price != NULL && strcmp(price, "Free to Play") == 0) {
        game->price = 0.0f;
    } else {
        game->price = atof(price);
    }
}

void setSupportedLanguages(Game* game, const char* supportedLanguages) {
    if (game->supportedLanguages) {
        for (int i = 0; i < game->supportedLanguagesCount; i++) {
            free(game->supportedLanguages[i]);
        }
        free(game->supportedLanguages);
    }
    game->supportedLanguages = formatarArrayString(supportedLanguages, 0, &game->supportedLanguagesCount);
}

void setMetacriticScore(Game* game, const char* metacriticScore) {
    game->metacriticScore = (metacriticScore == NULL || strlen(metacriticScore) == 0) ? -1 : atoi(metacriticScore);
}

void setUserScore(Game* game, const char* userScore) {
    if (userScore == NULL || strlen(userScore) == 0 || strcmp(userScore, "tbd") == 0) {
        game->userScore = -1.0f;
    } else {
        game->userScore = atof(userScore) * 10;
    }
}

void setAchievements(Game* game, const char* achievements) {
    game->achievements = (achievements == NULL || strlen(achievements) == 0) ? 0 : atoi(achievements);
}

void setPublishers(Game* game, const char* publishers) {
    if (game->publishers) {
        for (int i = 0; i < game->publishersCount; i++) {
            free(game->publishers[i]);
        }
        free(game->publishers);
    }
    char** temp = formatarArrayString(publishers, 0, &game->publishersCount);
    game->publishers = removerEspacosIniciais(temp, game->publishersCount);
    for(int i = 0; i < game->publishersCount; i++) free(temp[i]);
    free(temp);
}

void setDevelopers(Game* game, const char* developers) {
    if (game->developers) {
        for (int i = 0; i < game->developersCount; i++) {
            free(game->developers[i]);
        }
        free(game->developers);
    }
    char** temp = formatarArrayString(developers, 0, &game->developersCount);
    game->developers = removerEspacosIniciais(temp, game->developersCount);
    for(int i = 0; i < game->developersCount; i++) free(temp[i]);
    free(temp);
}

void setCategories(Game* game, const char* categories) {
    if (game->categories) {
        for (int i = 0; i < game->categoriesCount; i++) {
            free(game->categories[i]);
        }
        free(game->categories);
    }
    game->categories = formatarArrayString(categories, 0, &game->categoriesCount);
}

void setGenres(Game* game, const char* genres) {
    if (game->genres) {
        for (int i = 0; i < game->genresCount; i++) {
            free(game->genres[i]);
        }
        free(game->genres);
    }
    game->genres = formatarArrayString(genres, 1, &game->genresCount);
}

void setTags(Game* game, const char* tags) {
    if (game->tags) {
        for (int i = 0; i < game->tagsCount; i++) {
            free(game->tags[i]);
        }
        free(game->tags);
    }
    game->tags = formatarArrayString(tags, 1, &game->tagsCount);
}

// Funções auxiliares
bool compare(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

char** removerEspacosIniciais(char** array, int size) {
    if (array == NULL) return NULL;
    
    char** resultado = malloc(size * sizeof(char*));
    
    for (int i = 0; i < size; i++) {
        if (array[i] != NULL) {
            const char* p = array[i];
            while (*p && isspace((unsigned char)*p)) p++;
            resultado[i] = strdup(p);
        } else {
            resultado[i] = strdup("");
        }
    }
    return resultado;
}

// FUNÇÃO CORRIGIDA - agora preserva apóstrofos para tipo 1 (tags, gêneros)
char** formatarArrayString(const char* entrada, int tipo, int* count) {
    *count = 0;
    
    if (entrada == NULL || strlen(entrada) == 0) {
        return NULL;
    }

    // Contar vírgulas para estimar o número de elementos
    int virgulas = 0;
    for (int i = 0; entrada[i]; i++) {
        if (entrada[i] == ',') virgulas++;
    }
    
    char** resp = malloc((virgulas + 1) * sizeof(char*));
    char aux[MAX_FIELD_SIZE] = {0};
    int aux_idx = 0;
    int contador = 0;

    for (int i = 0; entrada[i]; i++) {
        char c = entrada[i];
        
        // Pular colchetes
        if (c == '[' || c == ']') continue;
        
        // Para tipo 0 (linguagens), pular aspas simples também
        // Para tipo 1 (tags, gêneros), preservar aspas simples
        if (tipo == 0 && c == '\'') continue;
        
        if (c == ',') {
            aux[aux_idx] = '\0';
            // Trim espaços
            char *start = aux;
            char *end = aux + aux_idx - 1;
            while (isspace((unsigned char)*start)) start++;
            while (end > start && isspace((unsigned char)*end)) end--;
            *(end + 1) = '\0';
            
            if (strlen(start) > 0) {
                resp[contador++] = strdup(start);
            }
            aux_idx = 0;
        } else {
            if (aux_idx < MAX_FIELD_SIZE - 1) {
                aux[aux_idx++] = c;
            }
        }
    }
    
    // Último elemento
    aux[aux_idx] = '\0';
    if (strlen(aux) > 0) {
        char *start = aux;
        char *end = aux + aux_idx - 1;
        while (isspace((unsigned char)*start)) start++;
        while (end > start && isspace((unsigned char)*end)) end--;
        *(end + 1) = '\0';
        
        if (strlen(start) > 0) {
            resp[contador++] = strdup(start);
        }
    }
    
    *count = contador;
    return resp;
}

void formatarArrayParaPrint(char** array, int count, char* resultado, int tipo) {
    resultado[0] = '\0';
    
    if (count == 0 || array == NULL) {
        strcpy(resultado, "[]");
        return;
    }
    
    strcpy(resultado, "[");
    for (int i = 0; i < count; i++) {
        strcat(resultado, array[i]);
        if (i < count - 1) {
            strcat(resultado, ", ");
        }
    }
    strcat(resultado, "]");
}

void pubOut(Game* game, char* resultado) {
    char linguas[MAX_FIELD_SIZE] = "[]";
    char publishers[MAX_FIELD_SIZE] = "[]";
    char developers[MAX_FIELD_SIZE] = "[]";
    char categories[MAX_FIELD_SIZE] = "[]";
    char genres[MAX_FIELD_SIZE] = "[]";
    char tags[MAX_FIELD_SIZE] = "[]";
    
    if (game->supportedLanguages != NULL) {
        formatarArrayParaPrint(game->supportedLanguages, game->supportedLanguagesCount, linguas, 0);
    }
    if (game->publishers != NULL) {
        formatarArrayParaPrint(game->publishers, game->publishersCount, publishers, 1);
    }
    if (game->developers != NULL) {
        formatarArrayParaPrint(game->developers, game->developersCount, developers, 1);
    }
    if (game->categories != NULL) {
        formatarArrayParaPrint(game->categories, game->categoriesCount, categories, 1);
    }
    if (game->genres != NULL) {
        formatarArrayParaPrint(game->genres, game->genresCount, genres, 1);
    }
    if (game->tags != NULL) {
        formatarArrayParaPrint(game->tags, game->tagsCount, tags, 1);
    }
    
    // Formatação do preço fixa em 2 casas decimais
    char priceStr[20];
    if (game->price == 0.0f) {
        strcpy(priceStr, "0.0");
    } else {
        sprintf(priceStr, "%.2f", game->price);

	char *dot = strchr(priceStr, '.');
        if (dot != NULL) {
            char *p = priceStr + strlen(priceStr) - 1;
            // Remove zeros à direita
            while (p > dot && *p == '0') {
                *p = '\0';
                p--;
            }
            // Se só sobrou o ponto, remove o ponto também
            if (p == dot) {
                *dot = '\0';
            }
	}
    }
    
    sprintf(resultado, "=> %d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %d ## %s ## %s ## %s ## %s ## %s ##",
            game->appID, game->name, game->releaseDate, game->estimatedOwners, priceStr,
            linguas, game->metacriticScore, game->userScore, game->achievements,
            publishers, developers, categories, genres, tags);
}

void sets(Game* game, char* array[]) {
    setAppID(game, array[0]);
    setName(game, array[1]);
    setReleaseDate(game, array[2]);
    setEstimatedOwners(game, array[3]);
    setPrice(game, array[4]);
    setSupportedLanguages(game, array[5]);
    setMetacriticScore(game, array[6]);
    setUserScore(game, array[7]);
    setAchievements(game, array[8]);
    setPublishers(game, array[9]);
    setDevelopers(game, array[10]);
    setCategories(game, array[11]);
    setGenres(game, array[12]);
    setTags(game, array[13]);
}

void freeGame(Game* game) {
    if (game->name) free(game->name);
    if (game->releaseDate) free(game->releaseDate);
    
    #define FREE_ARRAY(arr, count) \
        if (arr) { \
            for (int i = 0; i < count; i++) free(arr[i]); \
            free(arr); \
        }
    
    FREE_ARRAY(game->supportedLanguages, game->supportedLanguagesCount)
    FREE_ARRAY(game->publishers, game->publishersCount)
    FREE_ARRAY(game->developers, game->developersCount)
    FREE_ARRAY(game->categories, game->categoriesCount)
    FREE_ARRAY(game->genres, game->genresCount)
    FREE_ARRAY(game->tags, game->tagsCount)
}

int main() {
    FILE* arquivo = fopen("games.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo /tmp/games.csv\n");
        return 1;
    }

    Game dados[MAX_GAMES] = {0};
    int numGames = 0;
    char linha[MAX_LINE_SIZE];

    // Pular cabeçalho
    fgets(linha, MAX_LINE_SIZE, arquivo);

    while (fgets(linha, MAX_LINE_SIZE, arquivo) && numGames < MAX_GAMES) {
        linha[strcspn(linha, "\n")] = '\0';
        
        if (strlen(linha) == 0) continue;
        
        char* array[14] = {NULL};
        char aux[MAX_FIELD_SIZE] = {0};
        int contador = 0;
        int aux_idx = 0;
        bool aspas = false;

        for (int i = 0; linha[i]; i++) {
            char c = linha[i];
            if (c == '"') {
                aspas = !aspas;
            } else if (c == ',' && !aspas) {
                aux[aux_idx] = '\0';
                array[contador++] = strdup(aux);
                aux_idx = 0;
            } else {
                if (aux_idx < MAX_FIELD_SIZE - 1) {
                    aux[aux_idx++] = c;
                }
            }
        }
        aux[aux_idx] = '\0';
        array[contador] = strdup(aux);

        sets(&dados[numGames], array);
        numGames++;

        // Liberar array temporário
        for (int i = 0; i <= contador; i++) {
            if (array[i] != NULL) free(array[i]);
        }
    }
    
    fclose(arquivo);

    // Processar entradas do usuário
    char busca[MAX_INPUT_SIZE];
    
    while (fgets(busca, MAX_INPUT_SIZE, stdin)) {
        busca[strcspn(busca, "\n")] = '\0';
        
        if (compare(busca, "FIM")) {
            break;
        } else {
            int idBusca = atoi(busca);
            bool encontrado = false;
            
            for (int i = 0; i < numGames; i++) {
                if (idBusca == dados[i].appID) {
                    char resultado[MAX_LINE_SIZE];
                    pubOut(&dados[i], resultado);
                    printf("%s\n", resultado);
                    encontrado = true;
                    break;
                }
            }
            
            if (!encontrado) {
                printf("Game não encontrado\n");
            }
        }
    }

    // Liberar memória
    for (int i = 0; i < numGames; i++) {
        freeGame(&dados[i]);
    }

    return 0;
}
