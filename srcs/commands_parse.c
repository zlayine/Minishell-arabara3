
#include "../includes/shell.h"

t_cmds      *init_cmds(t_cmds   *prev)
{
    t_cmds  *cmds;

    cmds = malloc(sizeof(t_cmds));
    cmds->start = 0;
    cmds->end = 0;
    cmds->p = 0;
    cmds->append = 0;
    cmds->ret = 0;
    cmds->prev = NULL;
    if (prev)
        cmds->prev = prev;
    cmds->next = NULL;
    return (cmds);
}

char    *get_cmd(char *str, int n)
{
    int     i;
    char    *cmd;

    i = 0;
    while (!ft_isprint(*str) || *str == ' ')
        str++;
    if (n == 0)
        n = ft_strlen(str);
    while (ft_isprint(str[i]) && str[i] != ' ' && i < n)
        i++;
    cmd = malloc(sizeof(char) * (++i));
    ft_strlcpy(cmd, str, i);
    return (cmd);
}

char    **get_args(char *str, int n)
{
    int     i;
    char    *tmp;

    i = 0;
    tmp = ft_strdup(str);
    if (n != 0)
        tmp[n] = '\0';
    while (!ft_isalpha(*tmp))
        tmp++;
    return (ft_split(tmp, ' '));
}

t_shell     *parse_commands(t_shell *shell)
{
    t_cmds      *cmds;
    t_cmds      *prev;
    int         i;
    int         pos;
    char        *tmp;

    pos = 0;
    i = 0;
    tmp = shell->line;
    cmds = init_cmds(NULL);
    shell->cmds = cmds;
    while (tmp[i])
    {
        if (tmp[i] == '|')
        {
            cmds->cmd = get_cmd(tmp + pos, i - pos);
            cmds->args = get_args(tmp + pos, i - pos);
            // printf("POS:%d | I=%d\n", pos, i);
            // printf("CMD: %s|\n", cmds->cmd);
            // printf("ARG0: %s|\n", cmds->args[0]);
            // printf("ARG1: %s|\n---------------------------\n", cmds->args[1]);
            cmds->p = 1;
            if (!cmds->prev)
                cmds->start = 1;
            cmds->next = init_cmds(cmds);
            //printf("%s\n", cmds->next->prev->cmd);
            cmds = cmds->next;
            pos = i + 1;
        }
        else if (tmp[i] == ';' || tmp[i + 1] == '\0')
        {
            if (tmp[i + 1] == '\0')
            {
                cmds->cmd = get_cmd(tmp + pos, i - pos + 1);
                cmds->args = get_args(tmp + pos, i - pos + 1);
            }
            else
            {
                cmds->cmd = get_cmd(tmp + pos, i - pos);
                cmds->args = get_args(tmp + pos, i - pos);
            }
            // printf("POS:%d | I=%d\n", pos, i);
            // printf("CMD: %s|\n", cmds->cmd);
            // printf("ARG0: %s|\n", cmds->args[0]);
            // printf("ARG1: %s|\n--------------------------\n", cmds->args[1]);
            if (!cmds->prev)
                cmds->start = 1;
            cmds->end = 1;
            if (tmp[i + 1] != '\0')
            {
                cmds->next = init_cmds(cmds);
                cmds = cmds->next;
            }
            pos = i + 1;
        }
        else if (tmp[i] == '>' || tmp[i] == '<')
        {
            cmds->cmd = get_cmd(tmp + pos, i - pos);
            cmds->args = get_args(tmp + pos, i - pos);
            // printf("POS:%d | I=%d\n", pos, i);
            // printf("CMD: %s|\n", cmds->cmd);
            // printf("ARG0: %s|\n", cmds->args[0]);
            // printf("ARG1: %s|\n--------------------------\n", cmds->args[1]);
            if (!cmds->prev)
                cmds->start = 1;
            cmds->append = (tmp[i] == '>') ? 1 : -1;
            if (tmp[i + 1] == '>')
            {
                cmds->append++;
                i++;
            }
            pos = i + 1;
            cmds->next = init_cmds(cmds);
            cmds = cmds->next;
        }
        i++;
    }
    return (shell);
}

// --------------- TEST -------------------

// int main()
// {
//     t_shell *shell;
//     shell = malloc(sizeof(t_shell));

//     // shell->line = ft_strdup("echo -n \"hello\" | f.txt haha >> c.txt | grep h");
//     shell->line = ft_strdup("cat h.txt < f.txt;env |grep PATH|td -i;env|grep PWD");
//     //shell = get_single_command(shell);
//     //shell = control_command(shell);
//     // shell = get_comma_commands(shell);
//     shell = parse_commands(shell);
//     // printf("%s\n", shell->cmds->cmd);
// }
