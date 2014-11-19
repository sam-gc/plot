#ifndef SY_PARSER_H
#define SY_PARSER_H

typedef struct sy_node sy_node_t;
typedef struct {
    char *message;
    int location;
} sy_error_t;

sy_node_t *sy_parse_string(char *str, sy_error_t *err);
sy_node_t *sy_copy(sy_node_t *start);
double sy_evaluate(sy_node_t *node, double var);
double sy_evaluate_string(char *str, double var);
double sy_evaluate_string_with_error(char *str, double var, sy_error_t *err);

void sy_free(sy_node_t *node);
void sy_run_timer(sy_node_t *br, int reps);

#endif