#ifndef MAIN_HPP_RANU
#define MAIN_HPP_RANU

void crawl_directories(const char *root);
void help();
void usage();
char *create_and_change_dir(char *dirname, char *subdir);
void create_program_files(char *dirname);
void create_scratchpad_files(char *dirname);
void create_problem_files(char *dirname);

#endif
