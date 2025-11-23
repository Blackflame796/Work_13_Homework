#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL,"RUS");
    char str[1000];
    
    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);
    
    // Удаление символа новой строки, если он есть
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("В строке нет слов.\n");
        return 0;
    }
    
    int min_length = 1000; // Длина самого короткого слова
    int second_min_length = 1000; // Длина второго по минимальности слова
    int word_start = -1;
    char result[100] = ""; // искомое слово
    
    for (int i = 0; i <= len; i++) {
        // Если текущий символ не является пробелом и не концом строки
        // функция isspace находится в ctype.h
        if (i < len && !isspace(str[i])) {
            if (word_start == -1) {
                word_start = i; // Начало нового слова
            }
        } else {
            // Если слово найдено
            if (word_start != -1) {
                int word_end = i - 1;
                int word_len = word_end - word_start + 1;
                
                // Копирование текущего слова во временный буфер
                char current_word[100];
                for (int j = 0; j < word_len; j++) {
                    current_word[j] = str[word_start + j];
                }
                current_word[word_len] = '\0';
                
                // Обновляем минимальную длину
                if (word_len < min_length) {
                    second_min_length = min_length;
                    min_length = word_len;
                }
                
                // Нахождение слова, которое больше только самого короткого
                if (word_len > min_length) {
                    if (word_len < second_min_length) {
                        second_min_length = word_len;
                        strcpy(result, current_word);
                    } else if (word_len == second_min_length && strlen(result) == 0) {
                        // Первое слово с такой длиной
                        strcpy(result, current_word);
                    }
                }
                
                word_start = -1;
            }
        }
    }
    
    if (strlen(result) > 0) {
        printf("Слово, больше которого только самое короткое: %s\n", result);
    } else {
        printf("Все слова в строке имеют одинаковую длину.\n");
    }
    
    return 0;
}