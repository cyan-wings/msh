#include "ft_mem_utils.h"
#include "ft_string_utils.h"
#include "msh.h"

static int get_arr_length(t_list *env_list) {
	int i;

	i = 0;
	while (env_list) {
		env_list = env_list->next;
		i++;
	}
	return ++i;
}

static char *get_current_var(t_list *env_list) {
	t_env *current_env;
	char *res;
	size_t key_len;
	size_t val_len;

	current_env = (t_env *)env_list->content;
	key_len = ft_strlen(current_env->key);
	val_len = ft_strlen(current_env->val);
	res = ft_memalloc(key_len + val_len + 2);
	ft_strlcpy(res, current_env->key, key_len);
	ft_strlcpy(res + key_len, "=", key_len);
	ft_strlcpy(res + key_len + 1, current_env->val, val_len);
	return res;
}

char **msh_env_get_array(t_list *env_list) {
	char **env_arr;
	int i;

	env_arr = (char **)malloc(sizeof(char*) * (get_arr_length(env_list) + 1));
	i = 0;
	while(env_list) {
		env_arr[i++] = get_current_var(env_list);
		env_list = env_list->next;
	}
	env_arr[i] = 0;
	return env_arr;
}
