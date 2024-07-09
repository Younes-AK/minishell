#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

char *safe_allocation(size_t size) {
    char *ptr = (char *)malloc(size);
    if (!ptr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void ft_strcpy(char *dst, const char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

void ft_strcat(char *dst, const char *src) {
    while (*dst) {
        dst++;
    }
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

char *ft_strncpy(char *dest, const char *src, size_t n) {
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

size_t ft_strlen(const char *str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

char *ft_realloc(char *ptr, size_t new_size) {
    char *new_ptr = safe_allocation(new_size);
    ft_strcpy(new_ptr, ptr);
    free(ptr);
    return new_ptr;
}

char *append_char(char *res, char c, size_t *res_size) {
    size_t len = ft_strlen(res);
    if (len + 2 > *res_size) {
        *res_size = len + 2;
        res = ft_realloc(res, *res_size);
    }
    res[len] = c;
    res[len + 1] = '\0';
    return res;
}

char *append_value(char *res, const char *value, size_t *res_size) {
    size_t new_res_size = ft_strlen(res) + ft_strlen(value) + 1;
    if (new_res_size > *res_size) {
        *res_size = new_res_size;
        res = ft_realloc(res, *res_size);
    }
    ft_strcat(res, value);
    return res;
}

char *extract_var_name(const char **start) {
    const char *end = *start + 1;
    while (*end && (ft_isalnum(*end) || *end == '_' || *end == '@' || *end == '$')) {
        end++;
    }
    size_t var_size = end - *start - 1;
    char *var_name = safe_allocation(var_size + 1);
    ft_strncpy(var_name, *start + 1, var_size);
    var_name[var_size] = '\0';
    *start = end;
    return var_name;
}

char *get_env_value(const char *var_name, t_env *env_list) {
    if (strcmp(var_name, "$") == 0) {
        return "$";
    }
    if (strcmp(var_name, "$$") == 0) {
        int pid = getpid();
        return itoa(pid); // Assume `itoa` is implemented as shown earlier
    }
    t_env *iter = env_list;
    while (iter) {
        if (strcmp(iter->key, var_name) == 0) {
            return iter->value;
        }
        iter = iter->next;
    }
    return "";
}

char *replace(char *str, t_env *env_list) {
    char *result;
    size_t result_size;
    const char *start;
    char *var_name;
    const char *var_value;

    result_size = ft_strlen(str) + 1;
    result = safe_allocation(result_size);
    result[0] = '\0';
    start = str;

    while (*start) {
        if (*start == '$') {
            var_name = extract_var_name(&start);
            var_value = get_env_value(var_name, env_list);
            result = append_value(result, var_value, &result_size);
            free(var_name);
        } else {
            result = append_char(result, *start, &result_size);
            start++;
        }
    }
    free(str);
    return result;
}
