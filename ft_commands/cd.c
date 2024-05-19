#include "../../includes/minishell.h"
#include <errno.h>

char *get_env_name(char *dest, char *src) {
    int i = 0;
    while (src[i] && src[i] != '=' && ft_strlen(dest) < BUFF_SIZE) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

bool is_in_env(t_env *env, char *args) {
    char var_name[BUFF_SIZE];
    char env_var[BUFF_SIZE];

    get_env_name(var_name, args);
    while (env && env->next) {
        get_env_name(env_var, env->value);
        if (ft_strcmp(env_var, var_name) == 0) {
            ft_free(env->value);
            env->value = ft_strdup(args);
            return ERR;
        }
        env = env->next;
    }
    return SUCCESS;
}

int env_add(char *value, t_env *env) {
    t_env *new;
    t_env *tmp;

    if (env && env->value == NULL) {
        env->value = ft_strdup(value);
        return SUCCESS;
    }
    if ((new = (t_env *)malloc(sizeof(t_env))) == NULL) {
        return -1;
    }
    new->value = ft_strdup(value);
    while (env && env->next && env->next->next)
        env = env->next;
    tmp = env->next;
    env->next = new;
    new->next = tmp;
    return SUCCESS;
}

static int update_oldpwd(t_env *env) {
    char cwd[PATH_MAX];
    char *oldpwd;

    if (getcwd(cwd, PATH_MAX) == NULL) {
        return ERR;
    }
    if ((oldpwd = ft_strjoin("OLDPWD=", cwd)) == NULL) {
        return ERR;
    }
    if (is_in_env(env, oldpwd) == SUCCESS) {
        env_add(oldpwd, env);
    }
    ft_free(oldpwd);
    return SUCCESS;
}

static char *get_env_path(t_env *env, char *var, int len) {
    while (env && env->next != NULL) {
        if (ft_strncmp(env->value, var, len) == 0 && env->value[len] == '=') {
            return ft_strdup(env->value + len + 1);
        }
        env = env->next;
    }
    return NULL;
}

static int go_to_path(int opt, t_env *env) {
    int ret;
    char *env_path = NULL;

    if (opt == 0) {
        update_oldpwd(env);
        env_path = get_env_path(env, "HOME=", 5);
    } else if (opt == 1) {
        env_path = get_env_path(env, "OLDPWD=", 7);
    }
    if (env_path == NULL) {
        ft_putstr_fd(opt == 0 ? "cd: HOME not set\n" : "cd: OLDPWD not set\n", STDERR);
        return ERR;
    }
    ret = chdir(env_path);
    ft_free(env_path);
    return (ret == -1 ? ERR : SUCCESS);
}

void print_error(char **args) {
    ft_putstr_fd("cd: ", STDERR);
    if (args[2]) {
        ft_putstr_fd("string not in pwd: ", STDERR);
    } else {
        ft_putstr_fd(strerror(errno), STDERR);
        ft_putstr_fd(": ", STDERR);
    }
    ft_putstr_fd(args[1], STDERR);
    ft_putstr_fd("\n", STDERR);
}

int ft_cd(char **args, t_env *env) {
    int cd_ret;
    char *path;

    if (!args[1]) {
        return go_to_path(0, env);
    }
    if (args[1][0] == '~') {
        char *home_path = get_env_path(env, "HOME", 4);
        if (!home_path) {
            ft_putstr_fd("cd: HOME not set\n", STDERR);
            return ERR;
        }
        path = args[1][1] != '/' ? ft_strjoin(home_path, "/") : ft_strdup(home_path);
        char *temp = ft_strjoin(path, args[1] + 1);
        ft_free(path);
        path = temp;
        ft_free(home_path);
    } else {
        path = ft_strdup(args[1]);
    }

    if (ft_strcmp(path, "-") == 0) {
        cd_ret = go_to_path(1, env);
    } else {
        printf("path: %s\n", path);
        update_oldpwd(env);
        cd_ret = chdir(path);
        if (cd_ret < 0) {
            cd_ret *= -1;
            print_error((char *[2]){ "cd", path });
        }
    }
    ft_free(path);
    return (cd_ret);
}
