#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <io.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_FILENAME_LENGTH 1000
#define MAX_COMMIT_MESSAGE_LENGTH 2000
#define MAX_LINE_LENGTH 1000
#define MAX_MESSAGE_LENGTH 1000
#define debug(x) printf("%s", x);
void parse_date1(char *date_str, struct tm *tm);
time_t parse_commit_date(char *date_str) ;
int tedede_khotoot(char filename []);
int teedade_kaleme(char a[]);
bool is_count(char *string) ;
void remove_spase(char line[]);
void print_command(int argc, char * const argv[]);
int being_alias(int argc, char * const argv[]);
int run_config(int argc, char * const argv[]);
int global_username (char *username);
int global_email (char *email);
int local_username (char *username);
int local_email (char *email);
int run_init(int argc, char * const argv[]);
int create_configs(char *username, char *email);
int find_username(char*username);
int find_email(char*email);
int run_congig_alias(int argc, char * const argv[]);
int run_config_global_alis(int argc, char * const argv[]);
int run_add(int argc, char * const argv[]);
int add_to_staging(char *filepath);
int add_to_staging2(char *filepath);
int run_add_n (int argc, char *const argv[]);
int run_reset(int argc, char * const argv[]);
int reset_undo();
int remove_from_staging(char *filepath);
int remove_from_staging2(char *filepath) ;
int run_commit(int argc, char * const argv[]);
int runing_commite(char message[],int commit_ID);
int find_message_from_shorcut(char *message,char *const argv[]);
int inc_last_commit_ID();
bool check_file_directory_exists(char *filepath);
int commit_staged_file(int commit_ID, char *filepath);
int track_file(char *filepath);
bool is_tracked(char *filepath);
int create_commit_file(int commit_ID, char *message);
int find_file_last_commit(char* filepath);
int run_checkout(int argc, char *const argv[]);
int find_file_last_change_before_commit(char *filepath, int commit_ID);
int replace_shortcut (int argc, char * const argv[]);
int remove_shortcut (int argc, char * const argv[]);
int creat_shortcut(int argc, char * const argv[]);
int run_status();
bool is_staged(char *filepath) ;
int mogayese_file_va_last_commit(char* filepath,int file_last_commit_ID);
int find_username_for_commit(char username[], int commit_ID);
int find_branch(char username[], int commit_ID);
int find_message(char username[], int commit_ID);
int find_teedade_filehaye_commit_shode(char teedade_filehaye_commit_shode[], int commit_ID);
int run_log (int argc, char * const argv[]);
int run_just_log();
int run_log_n(char a[]);
int run_log_branch(char a[]);
int run_log_username(char a[]);
int run_log_search(char a[]);
int run_log_since(char a[]);
int run_log_before(char a[]);
void show_commit(int commit_ID);
int moghayese_ba_zamane_commit(time_t distans,int commit_id);
int run_branch(int argc, char *argv[]);
int show_branchs();
int commit_whith_branch (char branch_name []);
bool is_branched(char branch_name[]);
int find_last_commit_ID();
int checkout_file(char *filepath, int commit_ID);
int find_last_commit_id_of_branch(char branch_name []);
int altering_branch(char branch_name []);
int find_branch_from_config(char branch_name []);
int moghyese_last_commit_va_checkout_last_commit();
int altering_checkout_commit_id(int commit_id);
int find_head_commit_id();
int run_revert(int argc, char *argv[]);
int run_revrt_m_id(int argc, char * const argv[]);
int run_revrt_n_id(int argc, char * const argv[]);
int run_revrt_x_id(int argc, char * const argv[]);
int run_tag(int argc, char * const argv[]);
int show_tags();
int show_tag_name(char tag_name []);
int tag_a(int argc, char * const argv[]);
bool is_taged(char tag_name[]);
int remove_tag(char tag_name[]);
int run_diff(int argc, char * const argv[]);
int run_diff_f(char filename1[],int beggin1,int end1,char filename2[],int beggin2,int end2);
int run_diff_c(int commit_id1,int commit_id2);
bool is_commited(char *filepath,int commite_id);
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }
    print_command(argc, argv);
    if(being_alias(argc, argv))
    argc=being_alias(argc, argv);
    if (strcmp(argv[1], "init") == 0) {
        return run_init(argc, argv);
    } else if (strcmp(argv[1], "add") == 0&&strcmp(argv[2], "-n") == 0){
        return run_add_n(argc, argv);
    } else if (strcmp(argv[1], "add") == 0) {
        int a=tedede_khotoot(".neogit/staging");
        if(!run_add(argc, argv)){
            FILE *file = fopen(".neogit/teedade_stages", "w");
            fprintf(file, "%d\n", tedede_khotoot(".neogit/staging"-a)); 
        }
        return 0; 
    } else if (strcmp(argv[1], "reset") == 0) {
        return run_reset(argc, argv);
    } else if (strcmp(argv[1], "set") == 0&&strcmp(argv[2], "-m") == 0){
        return creat_shortcut(argc, argv);
    }else if (strcmp(argv[1], "commit") == 0) {
        return run_commit(argc, argv);
    } else if (strcmp(argv[1], "config") == 0&&(strncmp(argv[2],"alias.",6)==0||(strcmp(argv[2],"(-global)")==0&&strncmp(argv[3],"alias.",6)==0))) {
        return run_congig_alias(argc, argv);
    }else if (strcmp(argv[1], "config") == 0) {
        return run_config(argc, argv);
    } else if (strcmp(argv[1], "checkout") == 0) {
        return run_checkout(argc, argv);
    }else if (strcmp(argv[1], "replace") == 0&&strcmp(argv[2], "-s")==0){
        if(replace_shortcut(argc, argv))
        perror("There isn't this shortcut");
    }else if (strcmp(argv[1], "remove") == 0&&strcmp(argv[2], "-s")==0){
        if(remove_shortcut(argc, argv))
        perror("There isn't this shortcut");
        return 0;
    }else if (strcmp(argv[1], "status") == 0&&argc==2){
        return run_status();
    } else if (strcmp(argv[1], "log") == 0){
        return run_log(argc, argv);
    } else if (strcmp(argv[1], "branch") == 0){
        return run_branch(argc, argv);
    } else if (strcmp(argv[1], "revert") == 0){
        return run_revert(argc, argv);
    }else if (strcmp(argv[1], "tag") == 0){
        return run_tag(argc, argv);
    }else if (strcmp(argv[1], "diff") == 0){
        return run_diff(argc, argv);
    }
    return 0;
}
void print_command(int argc, char * const argv[]) {
    for (int i = 0; i < argc; i++) {
        fprintf(stdout, "%s ", argv[i]);
    }
    fprintf(stdout, "\n");
}
int being_alias(int argc, char * const argv[]){
    FILE*file=fopen(".neogit/alias","r");
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        int i=0;
        if (strcmp(line,argv[1]) == 0){
        if(fgets(line, sizeof(line), file) != NULL)
        while(line[0]==':'){
            strcpy(line,line+1);
            strcpy(argv[i],line);
            i++;
        }
        fclose(file);
        return i;
        }
    }
    fclose(file);
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 0;
    char tmp_cwd[1024];
    struct dirent *entry;
    do {
        // find .neogit
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 0;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".neogit") == 0){
                FILE *file=fopen("alias","r");
                if(file!=NULL) {
                    while (fgets(line, sizeof(line), file) != NULL) {
                    int length = strlen(line);
                    if (length > 0 && line[length - 1] == '\n') {
                    line[length - 1] = '\0';
                    }
                    int i=0;
                    if (strcmp(line,argv[1]) == 0){
                    if(fgets(line, sizeof(line), file) != NULL)
                    while(line==":"){
                    strcpy(line,line+1);
                    strcpy(argv[i],line);
                    i++;
                    }
                    fclose(file);
                    closedir(dir);
                    return i;
                    }
                    }
                }
                closedir(dir);
                return 0;
                }
            }
        closedir(dir);
        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 0;
        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 0;
        }
    } while (strcmp(tmp_cwd, "/") != 0);
    return 0;
}
int run_config(int argc, char * const argv[]){
    if(strcmp(argv[2],"-global")==0&&strcmp(argv[3],"user.name")==0&&argc>4) return global_username(argv[4]);
    if(strcmp(argv[2],"-global")==0&&strcmp(argv[3],"user.email")==0&&argc>4) return global_email(argv[4]);
    if(strcmp(argv[2],"user.name")==0) local_username (argv[3]); 
    if(strcmp(argv[2],"user.email")==0) local_email(argv[3]);
}
int global_username (char *username){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    struct dirent *entry;
    do {
        // find .neogit
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".neogit") == 0){
                FILE *file = fopen("global", "r");
                if (file != NULL){ 
                FILE *tmp_file = fopen("tmp_global", "w");
                if (tmp_file == NULL) return -1;
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), file) != NULL) {
                if (strncmp(line, "username:", 9) == 0) {
                strcpy(line+9,line+strlen(line));
                strcat(line,username);
                }
                fprintf(tmp_file, "%s\n", line);
                }
                fclose(file);
                fclose(tmp_file);
                remove("global");
                rename("tmp_global", "global");
                return 0;
                }
                else{
                file = fopen("global", "w");
                fprintf(file, "username:%s\n", username);
                fclose(file);
                return 0;
                }
            }
        }
        closedir(dir);
        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 1;
        }
    } while (strcmp(tmp_cwd, "/") != 0);
    return 1;
}
int global_email (char *email){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    struct dirent *entry;
    do {
        // find .neogit
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".neogit") == 0){
                FILE *file = fopen("global", "r");
                if (file != NULL){ 
                FILE *tmp_file = fopen("tmp_global", "w");
                if (tmp_file == NULL) return -1;
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), file) != NULL) {
                if (strncmp(line, "email:", 6) == 0) {
                strcpy(line+6,line+strlen(line));
                strcat(line,email);
                }
                fprintf(tmp_file, "%s\n", line);
                }
                fclose(file);
                fclose(tmp_file);
                remove("global");
                rename("tmp_global", "global");
                fclose(file);
                closedir(dir);
                return 0;
                }
                else{
                file = fopen("global", "w");
                fprintf(file, "email:%s\n", email);
                fclose(file);
                closedir(dir);
                return 0;
                }
            }
        }
        closedir(dir);
        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 1;
        }
    } while (strcmp(tmp_cwd, "/") != 0);
    return 1;
}
int local_username (char *username){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    FILE *tmp_file = fopen(".neogit/tmp_config", "w");
    if (tmp_file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "username:", 9) == 0) {
            strcpy(line+9,line+strlen(line));
            strcat(line,username);
        }
        fprintf(tmp_file, "%s\n", line);
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/config");
    rename(".neogit/tmp_config", ".neogit/config");
    return 0;
}
int local_email (char *email){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    FILE *tmp_file = fopen(".neogit/tmp_config", "w");
    if (tmp_file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "email:", 6) == 0) {
            strcpy(line+6,line+strlen(line));
            strcat(line,email); 
        }
        fprintf(tmp_file, "%s\n", line);
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/config");
    rename(".neogit/tmp_config", ".neogit/config");
    return 0;
}
int run_init(int argc, char * const argv[]) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    bool exists = false;
    struct dirent *entry;
    do {
        // find .neogit
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".neogit") == 0)
                exists = true;
        }
        closedir(dir);
        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 1;
        }
    } while (strcmp(tmp_cwd, "/") != 0);
    // return to the initial cwd
    if (chdir(cwd) != 0) return 1;
    if (!exists) {
        if (mkdir(".neogit") != 0) return 1;{
            char username[50],email[50];
            if(find_username(username)||find_email(email))
            return 1;
            return create_configs(username, email);
        }
    } else {
        perror("neogit repository has already initialized");
    }
    return 0;
}
int create_configs(char *username, char *email) {
    FILE *file = fopen(".neogit/config", "w");
    if (file == NULL) return 1;
    fprintf(file, "username: %s\n", username);
    fprintf(file, "email: %s\n", email);
    fprintf(file, "last_commit_ID: %d\n", 0);
    fprintf(file, "current_commit_ID: %d\n", 0);
    fprintf(file, "checkout_commit_ID: %d\n", 0);
    fprintf(file, "branch: %s", "master");
    fclose(file);
    // create commits folder
    if (mkdir(".neogit/commits") != 0) return 1;
    // create files folder
    if (mkdir(".neogit/files") != 0) return 1;
    file = fopen(".neogit/staging", "w");
    fclose(file);
    file = fopen(".neogit/branchs", "w");
    fprintf(file, "master");
    fclose(file);
    file = fopen(".neogit/directorystaging", "w");
    fclose(file);
    file = fopen(".neogit/tracks", "w");
    fclose(file);
    file = fopen(".neogit/alias", "w");
    fclose(file);
    return 0;
}
int find_username(char*username){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    struct dirent *entry;
    do {
        // find .neogit
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".neogit") == 0){
                FILE *file = fopen("global", "r");
                if (file != NULL){ 
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), file) != NULL) {
                if (strncmp(line, "username:", 9) == 0) {
                strcpy(line,line+9);
                strcpy(username,line);
                fclose(file);
                return 0;
                }
                }
                fclose(file);
                closedir(dir);
                }
                else{
                closedir(dir);
                fclose(file);
                return 1;
                }
            }
        }
        closedir(dir);
        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 1;
        }
    } while (strcmp(tmp_cwd, "/") != 0);
    return 1;
}
int find_email(char*email){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    struct dirent *entry;
    do {
        // find .neogit
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".neogit") == 0){
                FILE *file = fopen("global", "r");
                if (file != NULL){ 
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), file) != NULL) {
                if (strncmp(line, "email:", 6) == 0) {
                strcpy(line,line+6);
                strcpy(email,line);
                fclose(file);
                return 0;
                }
                }
                fclose(file);
                closedir(dir);
                }
                else{
                closedir(dir);
                fclose(file);
                return 1;
                }
            }
        }
        closedir(dir);
        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 1;
        }
    } while (strcmp(tmp_cwd, "/") != 0);
    return 1;
}
int run_congig_alias(int argc, char * const argv[]){
    if(strcmp(argv[2],"(-global)")==0){
        return run_config_global_alis(argc,argv);
    }
    else{
        FILE *file=fopen(".neogit/alias","a");
        strcpy(argv[2],argv[2]+6);
        fprintf(file,"%s\n",argv[2]);
        for(int i=3;i<argc;i++)
        fprintf(file,":%s\n",argv[i]);
        fclose(file);
        return 0;
    }
}
int run_config_global_alis(int argc, char * const argv[]){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    struct dirent *entry;
    do {
        // find .neogit
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".neogit") == 0){
                FILE *file=fopen("alias","a");
                if(file==NULL) 
                file=fopen("alias","w");
                strcpy(argv[2],argv[2]+6);
                fprintf(file,"%s\n",argv[2]);
                for(int i=3;i<argc;i++)
                fprintf(file,":%s\n",argv[i]);
                fclose(file);
                closedir(dir);
                return 0;
                }
            }
        closedir(dir);
        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 1;
        }
    } while (strcmp(tmp_cwd, "/") != 0);
    return 1;
}
int run_add(int argc, char *const argv[]) {
    // TODO: handle command in non-root directories 
    if (argc < 3) {
        perror("please specify a file");
        return 1;
    }
    int a;
    if(strstr(argv[2],"*")!=NULL){      
        struct _finddata_t f;
        int done;
        done=_findfirst(argv[2],&f);
        while (!done) {
            if(fopen(f.name ,"r")!=NULL)
            a= add_to_staging(f.name);
            else
            a= add_to_staging2(f.name);
            done=_findnext(f.attrib,&f);
        } 
        return a;
    }
    if(strcmp(argv[2],"-f")==0)
    for(int i=3;i<argc;i++){
    if(fopen(argv[i],"r")!=NULL){
    if(add_to_staging(argv[i]))
    perror("eror in adding");
    }
    else {
        DIR*dir;
        dir=opendir(argv[i]);
        if(dir!=NULL){
        if(add_to_staging2(argv[i]))
        perror("eror in adding");
        }
        else
        perror("this adderes is invalid");
    }
    return a;
    }
    if(fopen(argv[2],"r")!=NULL)
    return add_to_staging(argv[2]);
    DIR*dir;
    dir=opendir(argv[2]);
    if(dir!=NULL)
    return add_to_staging2(argv[2]);
    perror("this adderes is invalid");
}
int add_to_staging(char *filepath) {
    FILE *file = fopen(".neogit/staging", "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(filepath, line) == 0) return 0;
    }
    fclose(file);
    file = fopen(".neogit/staging","a");
    if (file == NULL) return 1;
    fprintf(file, "%s\n", filepath);
    fclose(file);
    return 0;
}
int add_to_staging2(char *filepath) {
    DIR *dir = opendir(filepath);
    struct dirent *entry;
        if (dir == NULL) {
            perror("Error opening directory");
            return 1;
        }
        FILE*file= fopen(".neogit/directorystaging", "a");
        fprintf(file, "%s\n", filepath);
        fclose(file);
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR){
            if(add_to_staging2(entry->d_name))
            perror("Error opening directory");
            }   
            else{
            if(add_to_staging(entry->d_name))
            perror("Error opening directory");
            }   
        }
        closedir(dir);
        return 0;
}
int run_add_n (int argc, char *const argv[]){
    if(argc>3){
        perror("invalid command");
        return 1;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    struct dirent *entry;
    DIR *dir = opendir(".");
    int check=0;
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        FILE *file;
        while ((entry = readdir(dir)) != NULL) {
            if (fopen(entry->d_name,"r")!=NULL){
                FILE *file = fopen(".neogit/staging", "r");
                if (file == NULL) return 1;
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), file) != NULL) {
                int length = strlen(line);
                if (length > 0 && line[length - 1] == '\n') {
                line[length - 1] = '\0';
                }
                if (strcmp(entry->d_name, line) == 0){
                    check=1;
                    fclose(file);
                    break;
                }
                }
                fclose(file);
                }
            if(opendir(entry->d_name)!=NULL){
                FILE *file = fopen(".neogit/directorystaging", "r");
                if (file == NULL) return 1;
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), file) != NULL) {
                int length = strlen(line);
                if (length > 0 && line[length - 1] == '\n') {
                line[length - 1] = '\0';
                }
                if (strcmp(entry->d_name, line) == 0){
                    check=1;
                    fclose(file);
                    break;
                }
                }
                fclose(file);
            }
            if(check){printf("%s is staged\n",entry->d_name);}
            else{printf("%s isn't staged\n",entry->d_name);}
        }
        closedir(dir);
}
int run_reset(int argc, char *const argv[]) {
    // TODO: handle command in non-root directories 
    if (argc < 3) {
        perror("please specify a file");
        return 1;
    }
    if(strcmp(argv[2],"-undo")==0){
        if(reset_undo)
        return 1; 
        return 0;       
    }
    if(fopen(argv[2],"r")!=NULL)
    return remove_from_staging(argv[2]);
    DIR*dir=opendir(argv[2]);
    struct dirent *entry;
    if(dir!=NULL){
        while ((entry = readdir(dir)) != NULL) {
            if(fopen(entry->d_name,"r")!=NULL){
            if(remove_from_staging(entry->d_name))
            perror("Error removing files"); }
            else if(remove_from_staging2(entry->d_name)) 
            perror("Error removing diorectory"); 
        }
        closedir(dir);
        return 0;
    }    
    perror("this adderes is invalid"); 
    return 1;   
}
int remove_from_staging(char *filepath) {
    FILE *file = fopen(".neogit/staging", "r");
    if (file == NULL) return 1;
    FILE *tmp_file = fopen(".neogit/tmp_staging", "w");
    if (tmp_file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(filepath, line) != 0) fputs(line, tmp_file);
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/staging");
    rename(".neogit/tmp_staging", ".neogit/staging");
    return 0;
}
int remove_from_staging2(char *filepath) {
    FILE *file = fopen(".neogit/directorystaging", "r");
    if (file == NULL) return 1;
    FILE *tmp_file = fopen(".neogit/temp_directorystaging", "w");
    if (tmp_file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(filepath, line) != 0) fputs(line, tmp_file);
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/directorystaging");
    rename(".neogit/tmp_staging", ".neogit/directorystaging");
    DIR*dir=opendir(filepath);
    struct dirent *entry;
    if(dir!=NULL){
        while ((entry = readdir(dir)) != NULL) {
            if(fopen(entry->d_name,"r")!=NULL){
            if(remove_from_staging(entry->d_name))
            perror("Error removing files"); }
            else if(remove_from_staging2(entry->d_name)) 
            perror("Error removing diorectory"); 
        }
        closedir(dir);
        return 0;
    } }   
int reset_undo(){
    FILE *file = fopen(".neogit/teedade_stages", "r");
    int a;
    fscanf(file,"%d",&a);
    int b=tedede_khotoot(".neogit/staging");
    fclose(file);
    file = fopen(".neogit/staging", "r");
    if (file == NULL) return 1;
    FILE *tmp_file = fopen(".neogit/tmp_staging", "w");
    if (tmp_file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        fputs(line, tmp_file);
        b--;
        if(!b-a)
        break;
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/staging");
    rename(".neogit/tmp_staging", ".neogit/staging");
    return 0;
}
int run_commit(int argc, char * const argv[]) {
    if (argc < 4) {
        perror("please use the correct format");
        return 1;
    }
    if(moghyese_last_commit_va_checkout_last_commit){
        perror("you should checkout to jead for commit");
        return 1;
    }
    if(argc>4&&(argv[3][0]!='['||argv[argc-1][strlen(argv[argc-1])-1]!=']')){
        perror("invalid comit masage");
        return 1;
    }
    char message[MAX_MESSAGE_LENGTH];
    if(strcmp(argv[2], "-s") == 0){
        if(find_message_from_shorcut(message,argv))
        printf("There is no shirtcut\n");
    }
    else if(strcmp(argv[2], "-m") == 0){
        for(int i=3;i<argc;i++)
        {strcat(message, argv[i]);}
    }
    if(strlen(message)>72){
        perror("the comit message is too long!");
        return 1;
    }
    int commit_ID = inc_last_commit_ID();
    if (commit_ID == -1) return 1;
    return runing_commite(message,commit_ID);
}
// returns new commit_ID
int runing_commite(char message[],int commit_ID){
    FILE *file = fopen(".neogit/staging", "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (!check_file_directory_exists(line)) {
            char dir_path[MAX_FILENAME_LENGTH];
            strcpy(dir_path, ".neogit/files/");
            strcat(dir_path, line);
            if (mkdir(dir_path) != 0) return 1;
        }
        printf("commit %s\n", line);
        commit_staged_file(commit_ID, line);
        track_file(line);
    }
    fclose(file); 
    // free staging
    file = fopen(".neogit/staging", "w");
    if (file == NULL) return 1;
    fclose(file);
    create_commit_file(commit_ID, message);
    fprintf(stdout, "commit successfully with commit ID %d", commit_ID);
    return 0;
}
int find_message_from_shorcut(char *message,char *const argv[]){
    FILE*file=fopen(".neogit/shortcuts","r");
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(line,argv[3]) == 0){
        if(fgets(line, sizeof(line), file) != NULL)
        while(line[0]==':'){
            strcpy(line,line+1);
            strcpy(message,line);
        }
        fclose(file);
        return 0;
        }
    }
    fclose(file);
    return 1;
}
int inc_last_commit_ID() {
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    FILE *tmp_file = fopen(".neogit/tmp_config", "w");
    if (tmp_file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            last_commit_ID++;
            fprintf(tmp_file, "last_commit_ID: %d\n", last_commit_ID);
        } else if(strncmp(line, "checkout_commit_ID:", 19) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            last_commit_ID++;
            fprintf(tmp_file, "last_commit_ID: %d\n", last_commit_ID);
        } else fprintf(tmp_file, "%s", line);
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/config");
    rename(".neogit/tmp_config", ".neogit/config");
    return last_commit_ID;
}
bool check_file_directory_exists(char *filepath) {
    DIR *dir = opendir(".neogit/files");
    struct dirent *entry;
    if (dir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, filepath) == 0) return true;
    }
    closedir(dir);
    return false;
}
int commit_staged_file(int commit_ID, char* filepath) {
    FILE *read_file, *write_file;
    char read_path[MAX_FILENAME_LENGTH];
    strcpy(read_path, filepath);
    char write_path[MAX_FILENAME_LENGTH];
    strcpy(write_path, ".neogit/files/");
    strcat(write_path, filepath);
    strcat(write_path, "/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(write_path, tmp);
    read_file = fopen(read_path, "r");
    if (read_file == NULL) return 1;
    write_file = fopen(write_path, "w");
    if (write_file == NULL) return 1;
    char buffer;
    buffer = fgetc(read_file);
    while(buffer != EOF) {
        fputc(buffer, write_file);
        buffer = fgetc(read_file);
    }
    fclose(read_file);
    fclose(write_file);
    return 0;
}
int track_file(char *filepath) {
    if (is_tracked(filepath)) return 0;
    FILE *file = fopen(".neogit/tracks", "a");
    if (file == NULL) return 1;
    fprintf(file, "%s\n", filepath);
    return 0;
}
bool is_tracked(char *filepath) {
    FILE *file = fopen(".neogit/tracks", "r");
    if (file == NULL) return false;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(line, filepath) == 0) return true;
    }
    fclose(file); 
    return false;
}
int create_commit_file(int commit_ID, char *message) {
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);
    FILE *file = fopen(commit_filepath, "w");
    if (file == NULL) return 1;
    fprintf(file, "message: %s\n", message);
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    fprintf(file, "time: %s\n", asctime(localTime));
    FILE *file1 = fopen(".neogit/config", "r");
    if (file1 == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    char a[100];
    while (fgets(line, sizeof(line), file1) != NULL) {
        if (strncmp(line, "username: ", 10) == 0) {
            sscanf(line, "username: %s\n", &a);
            fprintf(file, "username: %s\n",a);
            break;            
        } 
    }
    rewind(file1);
    while (fgets(line, sizeof(line), file1) != NULL) {
        if (strncmp(line, "branch: ", 8) == 0) {
            sscanf(line, "branch: %s\n", &a);
            fprintf(file, "branch: %s\n",a);
            break;            
        } 
    }
    fclose(file1);
    fprintf(file, "teedade filehaye commit shode:%d\n",tedede_khotoot(".neogit/staging"));
    fprintf(file, "files:\n");
    DIR *dir = opendir(".");
    struct dirent *entry;
    if (dir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_tracked(entry->d_name)) {
            char filename[120];
            int file_last_commit_ID = find_file_last_commit(entry->d_name);
            strcpy(filename,cwd);
            strcat(filename,entry->d_name);
            fprintf(file, "%s %d\n",filename, file_last_commit_ID);
        }
    }
    closedir(dir); 
    fclose(file);
    return 0;
}
int find_file_last_commit(char* filepath) {
    char filepath_dir[MAX_FILENAME_LENGTH];
    strcpy(filepath_dir, ".neogit/files/");
    strcat(filepath_dir, filepath);
    int max = -1;
    DIR *dir = opendir(filepath_dir);
    struct dirent *entry;
    if (dir == NULL) return 1;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            int tmp = atoi(entry->d_name);
            max = max > tmp ? max: tmp;
        }
    }
    closedir(dir);
    return max;
}
int creat_shortcut(int argc, char * const argv[]){
    FILE *file=fopen(".neogit/shortcuts", "a");
    fprintf(file,"%s\n",argv[argc-1]);
    for(int i=3;i<argc-2;i++)
    fprintf(file,":%s\n",argv[i]);
    fclose(file);
    return 0;
}
int replace_shortcut (int argc, char * const argv[]){
    FILE*file=fopen(".neogit/shortcuts","r");
    FILE*tmp_file=fopen(".neogit/tmp_shortcuts","w");
    char line[MAX_LINE_LENGTH];
    int check=1;
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if(strcmp(line,argv[argc-1]) == 0){
            check=0;
            fprintf(tmp_file, "%s\n", line);
            for(int i=3;i<argc-2;i++)
            fprintf(file,":%s\n",argv[i]);
        }
        else if (line[0]!=':'){
        fprintf(tmp_file, "%s\n", line);
        }
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/shortcuts");
    rename(".neogit/tmp_shortcuts", ".neogit/shortcuts");
    return check;
}
int remove_shortcut (int argc, char * const argv[]){
    FILE*file=fopen(".neogit/shortcuts","r");
    FILE*tmp_file=fopen(".neogit/tmp_shortcuts","w");
    char line[MAX_LINE_LENGTH];
    int check=1;
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if(strcmp(line,argv[3]) == 0){
            check=0;
        }
        if (strcmp(line,argv[3]) != 0&&line[0]!=':'){
            fprintf(tmp_file, "%s\n", line);
        }
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/shortcuts");
    rename(".neogit/tmp_shortcuts", ".neogit/shortcuts");
    return check;
}
int run_status(){
    DIR *dir = opendir(".");
    struct dirent *entry;
    if (dir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            if(is_staged(entry->d_name)) printf("+");
            else printf("-"); 
            if(!is_tracked(entry->d_name)) printf("D\n"); 
            else{             
            int file_last_commit_ID = find_file_last_commit(entry->d_name);
            if(mogayese_file_va_last_commit(entry->d_name,file_last_commit_ID)) printf("A\n");
            else printf("M\n");
            }
        }
    }
    closedir(dir); 
    return 0;
}
bool is_staged(char *filepath) {
    FILE *file = fopen(".neogit/staging", "r");
    if (file == NULL) return false;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(line, filepath) == 0) return true;
    }
    fclose(file); 
    return false;
}
int mogayese_file_va_last_commit(char* filepath,int file_last_commit_ID) {
    FILE *read_file, *write_file;
    char read_path[MAX_FILENAME_LENGTH];
    strcpy(read_path, filepath);
    char write_path[MAX_FILENAME_LENGTH];
    strcpy(write_path, ".neogit/files/");
    strcat(write_path, filepath);
    strcat(write_path, "/");
    char tmp[10];
    sprintf(tmp, "%d",  file_last_commit_ID);
    strcat(write_path, tmp);
    if(tedede_khotoot(write_path)!=tedede_khotoot(read_path)) return 1;
    read_file = fopen(read_path, "r");
    if (read_file == NULL) return 1;
    write_file = fopen(write_path, "r");
    if (write_file == NULL) return 1;
    char buffer1;
    char buffer2;
    buffer1 = fgetc(read_file);
    buffer2 = fgetc(write_file);
    while(buffer1 != EOF&&buffer2 != EOF) {
        if(buffer1!=buffer2){
            fclose(read_file);
            fclose(write_file);
            return 1;
        }
        buffer1 = fgetc(read_file);
        buffer2 = fgetc(write_file);
    }
    fclose(read_file);
    fclose(write_file);
    return 0;
}
int find_username_for_commit(char username[], int commit_ID){
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);
    FILE *file = fopen("commit_filepath", "r");
    if (file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "username: ", 10) == 0) {
            sscanf(line, "username: %s\n", &username);
            fclose(file);
            return 0;            
        } 
    }
    fclose(file);
    return -1;
}
int find_branch(char branch[], int commit_ID){
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);
    FILE *file = fopen(commit_filepath, "r");
    if (file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "branch: ", 8) == 0) {
            sscanf(line, "branch: %s\n", &branch);
            fclose(file);
            return 0;            
        } 
    }
    fclose(file);
    return -1;
}
int find_time(char time[], int commit_ID){
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);
    FILE *file = fopen("commit_filepath", "r");
    if (file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "time: ", 6) == 0) {
            sscanf(line, "time: %s\n", &time);
            fclose(file);
            return 0;            
        } 
    }
    fclose(file);
    return -1;
}
int find_message(char message[], int commit_ID){
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp); 
    FILE *file = fopen(commit_filepath, "r");
    if (file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "message: ", 9) == 0) {
            sscanf(line, "message: %s\n", &message);
            fclose(file);
            return 0;            
        } 
    }
    fclose(file);
    return -1;
}
int find_teedade_filehaye_commit_shode(char teedade_filehaye_commit_shode[], int commit_ID){
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);
    FILE *file = fopen("commit_filepath", "r");
    if (file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "teedade filehaye commit shode: ", 31) == 0) {
            sscanf(line, "teedade filehaye commit shode: %s\n", &teedade_filehaye_commit_shode);
            fclose(file);
            return 0;            
        } 
    }
    fclose(file);
    return -1;
}
int run_log (int argc, char * const argv[]){
    if(argc==2) return run_just_log();
    if(strcmp(argv[2],"-n")==0&&argc==4) return run_log_n(argv[3]);
    if(strcmp(argv[2],"-branch")==0&&argc==4) return run_log_branch(argv[3]);
    if(strcmp(argv[2],"-author")==0&&argc==4) return run_log_username(argv[3]);
    if(strcmp(argv[2],"-search")==0&&argc==4) return run_log_search(argv[3]);
    if(strcmp(argv[2],"-since")==0&&argc==4) return run_log_since(argv[3]);
    if(strcmp(argv[2],"-before")==0&&argc==4) return run_log_before(argv[3]);
    return 1;
}
int run_just_log(){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    for(int i=last_commit_ID;i>0;i--){
        show_commit(i);}
    return 0;
}
int run_log_n(char a[]){
    int n=atoi(a);
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    for(int i=last_commit_ID;i>last_commit_ID-n;i--){
        show_commit(i);}
    return 0;
}
int run_log_branch(char a[]){
    int check=1;
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    for(int i=last_commit_ID;i>0;i--){
        char branch[100];
        if(!find_branch(branch,i)){
            if(strcmp(branch,a)==0){
                check=0;
                show_commit(i);
                }
            }
        else return -1;
    }
    if(check)
    perror("There is no commits for this branch");
    return 0;
}
int run_log_username(char a[]){
    int check=1;
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    for(int i=last_commit_ID;i>0;i--){
        char username[100];
        if(!find_username_for_commit(username,i)){
            if(strcmp(username,a)==0){
                check=0;
                show_commit(i);
                }
            }
        else return -1;
    }
    if(check)
    perror("There is no commits for this username");
    return 0;
}
int run_log_search(char a[]){
    int check=1;
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    for(int i=last_commit_ID;i>0;i--){
        char word[100];
        if(!find_message(word,i)){
            if(strstr(word,a)!=NULL){
                check=0;
                show_commit(i);
                }
            }
        else return -1;
    }
    if(check)
    perror("There is no this word in any commit");
    return 0;
}
int run_log_since(char a[]){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    time_t distance = parse_commit_date(a);
    for(int i=last_commit_ID;i>0;i--){
        if(moghayese_ba_zamane_commit(distance,i)==0){show_commit(i);}
        else break;
    }
    return 0;
}
int run_log_before(char a[]){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    time_t distance = parse_commit_date(a);
    for(int i=last_commit_ID;i>0;i--){
        if(moghayese_ba_zamane_commit(distance,i)==1){show_commit(i);}
    }
    return 0;
}
void show_commit(int commit_ID){
    int i=commit_ID;
    char a[100];
        printf("comit ID=%d",i);
        if(!find_message(a,i))
        printf(" message: %s",a);
        if(!find_username_for_commit(a,i))
        printf(" username: %s",a);
        if(!find_time(a,i))
        printf(" time: %s",a);
        if(!find_branch(a,i))
        printf(" branch: %s",a);
        if(!find_teedade_filehaye_commit_shode(a,i))
        printf("teedede filehaye commit shode: %s\n",a);
}
int moghayese_ba_zamane_commit(time_t distans,int commit_id){
    char time[40];
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_id);
    strcat(commit_filepath, tmp);
    FILE *file = fopen("commit_filepath", "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "time: ", 6) == 0) {
            sscanf(line, "time: %s\n", &time);
            fclose(file);
            break;;            
        } 
    }
    fclose(file);
    if(parse_commit_date(time)>distans)
    return 0;
    else if(parse_commit_date(time)<=distans)
    return 1;
    return -1;
}
int run_branch(int argc, char *argv[]){
    if(argc==2) return show_branchs();
    if(argc==3) return commit_whith_branch(argv[2]);
    return 1;
}
int commit_whith_branch (char branch_name []){
    if(is_branched(branch_name)) {
        perror("This name is ulitized");
        return 1;
    }
    int commit_ID=find_last_commit_ID();
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);
    FILE *file = fopen(commit_filepath, "r");
    if (file == NULL) return 1;
    FILE *tmp_file = fopen(".neogit/commits/tmp", "w");
    if (tmp_file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "branch: ", 8) == 0) {
            strcpy(line+8,line+strlen(line));
            strcat(line,branch_name);
            strcat(line,"\n");
        }
        fprintf(tmp_file, "%s", line);
    }
    fclose(file);
    fclose(tmp_file);
    remove(commit_filepath);
    rename(".neogit/commits/tmp", commit_filepath);
    file = fopen(".neogit/branchs", "a");
    if (file == NULL) return 1;
    fprintf(file, "%s\n", branch_name);
    fclose(file);
    return 0;
}
int show_branchs(){
    FILE *file = fopen(".neogit/branchs", "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        puts(line);         
    } 
    fclose(file);
    return 0;
}
bool is_branched(char branch_name[]){
    FILE *file = fopen(".neogit/tracks", "r");
    if (file == NULL) return false;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(line, branch_name) == 0) return true;
    }
    fclose(file); 
    return false;
}
int find_last_commit_ID() {
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            fclose(file);
            return last_commit_ID;
        } 
    }
    fclose(file);
    return -1;    
}
int run_checkout(int argc, char * const argv[]) {
    if (argc < 3) return 1;
    DIR *dir = opendir(".");
    struct dirent *entry;
    int commit_ID;
    if(strcmp(argv[2],"HEAD")==0){
        commit_ID =find_head_commit_id();
    }
    else if(is_count(argv[2])){
    commit_ID = atoi(argv[2]);}
    else {
        commit_ID =find_last_commit_id_of_branch(argv[2]);
    }
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_tracked(entry->d_name)) {
            if(mogayese_file_va_last_commit(entry->d_name,find_file_last_commit(entry->d_name))){
                printf("you should commit %s first\n",entry->d_name);
            }
            else checkout_file(entry->d_name, find_file_last_change_before_commit(entry->d_name, commit_ID));
        }
    }
    closedir(dir);
    if(altering_branch(argv[2]))
    return 1;
    if(!altering_checkout_commit_id(commit_ID))    
    return 0;
    return 1;
}
int find_file_last_change_before_commit(char *filepath, int commit_ID) {
    char filepath_dir[MAX_FILENAME_LENGTH];
    strcpy(filepath_dir, ".neogit/files/");
    strcat(filepath_dir, filepath);
    int max = -1;
    DIR *dir = opendir(filepath_dir);
    struct dirent *entry;
    if (dir == NULL) return 1;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            int tmp = atoi(entry->d_name);
            if (tmp > max && tmp <= commit_ID) {
                max = tmp;
            }
        }
    }
    closedir(dir);
    return max;
}
int checkout_file(char *filepath, int commit_ID) {
    char src_file[MAX_FILENAME_LENGTH];
    strcpy(src_file, ".neogit/files/");
    strcat(src_file, filepath);
    char tmp[10];
    sprintf(tmp, "/%d", commit_ID);
    strcat(src_file, tmp);
    FILE *read_file = fopen(src_file, "r");
    if (read_file == NULL) return 1;
    FILE *write_file = fopen(filepath, "w");
    if (write_file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), read_file) != NULL) {
        fprintf(write_file, "%s", line);
    }
    fclose(read_file);
    fclose(write_file);
    return 0;
}
int find_last_commit_id_of_branch(char branch_name1 []){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    int last_commit_ID;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    for(int i=last_commit_ID;i>0;i--){
        char branch_name2[100];
        if(!find_branch(branch_name2,i))
        if(strcmp(branch_name1,branch_name2)==0)
        return i;
    }
    return -1;
}
int altering_branch(char branch_name []){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    FILE *tmp_file = fopen(".neogit/tmp_config", "w");
    if (tmp_file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "branch: ", 8) == 0) {
            strcpy(line+8,line+strlen(line));
            strcat(line,branch_name);
        }
        fprintf(tmp_file, "%s\n", line);
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/config");
    rename(".neogit/tmp_config", ".neogit/config");
    return 0;
}
int find_branch_from_config(char branch_name []){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "branch: ", 8) == 0) {
            sscanf(line, "branch: %s\n", &branch_name);
            fclose(file);
            return 0;            
        } 
    }
    fclose(file);
    return 1;
}
int moghyese_last_commit_va_checkout_last_commit(){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return 1;
    int last_commit_ID,checkout_commit_ID;
    char line[MAX_LINE_LENGTH];
    int check1=0 , check2=0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            check1=1;
        } else if(strncmp(line, "checkout_commit_ID:", 19) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &checkout_commit_ID);
            check2=1;
        } 
        if(check1&&check2)
        {break;}
    }
    fclose(file);
    if(checkout_commit_ID==last_commit_ID)
    return 0;
    return -1;
}
int altering_checkout_commit_id(int commit_id){
    FILE *file = fopen(".neogit/config", "r");
    if (file == NULL) return -1;
    FILE *tmp_file = fopen(".neogit/tmp_config", "w");
    if (tmp_file == NULL) return -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "checkout_commit_ID:", 19) == 0) {
            strcpy(line+19,line+strlen(line));
            sprintf(line," %d",commit_id);
        }
        fprintf(tmp_file, "%s\n", line);
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/config");
    rename(".neogit/tmp_config", ".neogit/config");
    return 0;
}
int find_head_commit_id(){
    char branch[40];
    if(find_branch_from_config(branch))
    return 1;
    return find_last_commit_id_of_branch(branch);
}
void parse_date1(char *date_str, struct tm *tm) {
    sscanf(date_str, "%d-%d-%d-%d:%d:%d",
           &tm->tm_year, &tm->tm_mon, &tm->tm_mday,
           &tm->tm_hour, &tm->tm_min, &tm->tm_sec);
    tm->tm_year -= 1900;
    tm->tm_mon -= 1;
}
time_t parse_commit_date(char *date_str) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    parse_date1(date_str, &tm);
    return mktime(&tm);
}
int run_revert(int argc, char *argv[]){
    if(argc==3&&strncmp(argv[argc-1],"HEAD-",5)==0) return run_revrt_x_id(argc, argv);
    if(strcmp(argv[2],"-n")==0) return run_revrt_n_id(argc, argv);
    if(argc==3||(strcmp(argv[2],"-m")==0&&argc==5)) return run_revrt_m_id(argc, argv);
    return 1;
}
int run_revrt_m_id(int argc, char * const argv[]){
    int commit_ID= atoi(argv[argc-1]);
    char message[80];
    if(argc==3) strcpy(message,argv[2]);
    else if(find_message(message,commit_ID)) return 1; 
    DIR *dir = opendir(".");
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_tracked(entry->d_name)) {
          checkout_file(entry->d_name, find_file_last_change_before_commit(entry->d_name, commit_ID));
        }
    }
    closedir(dir);  
    commit_ID = inc_last_commit_ID();
    return runing_commite(message,commit_ID);
}
int run_revrt_n_id(int argc, char * const argv[]){
    int commit_ID;
    if(argc==3) commit_ID=find_last_commit_ID();
    else commit_ID=atoi(argv[3]);
    DIR *dir = opendir(".");
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_tracked(entry->d_name)) {
          checkout_file(entry->d_name, find_file_last_change_before_commit(entry->d_name, commit_ID));
        }
    }
    closedir(dir);  
    return 0;
}
int run_revrt_x_id(int argc, char * const argv[]){
    strcpy(argv[argc-1]+4,argv[argc-1]+strlen(argv[argc-1]));
    int commit_ID= find_last_commit_ID()-atoi(argv[argc-1]);
    char message[80];
    if(argc==3) if(find_message(message,commit_ID)) return 1; 
    else strcpy(message,argv[3]);
    DIR *dir = opendir(".");
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_tracked(entry->d_name)) {
          checkout_file(entry->d_name, find_file_last_change_before_commit(entry->d_name, commit_ID));
        }
    }
    closedir(dir);  
    commit_ID = inc_last_commit_ID();
    return runing_commite(message,commit_ID);
}
int run_tag(int argc, char * const argv[]){
    if(argc==2) return show_tags();
    if(strcmp(argv[2],"-a")==0) return tag_a(argc,argv);
    if (strcmp(argv[2],"show")==0) return show_tag_name(argv[3]);
    return 1;
}
int show_tags(){
    FILE *file = fopen(".neogit/tags", "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if(line[0]!=':')
        puts(line);         
    } 
    fclose(file);
    return 0;
}
int show_tag_name(char tag_name []){
    FILE *file = fopen(".neogit/tags", "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    int check1=0,check2=1;
    while (fgets(line, sizeof(line), file) != NULL) {
        if(strcmp(line,tag_name)==0&&check2){
            check1=1;
            check2=0;
            puts(line);
        }
        if(check1){
            if(line[0]==':'){
            strcpy(line,line+1);
            puts(line);
            }
            else  break;    
        }               
    } 
    fclose(file);
    return 0;
}
int tag_a(int argc, char * const argv[]){
    if(is_taged&&strcmp(argv[argc-1],"-f")!=0) {
        perror("There are a tag with this name");
        return 1;
    }
    if(is_taged&&strcmp(argv[argc-1],"-f")==0) {
        if(remove_tag(argv[3]))
        return 1;
    }
    FILE *file = fopen(".neogit/tags", "a");
    if (file == NULL) return 1;
    fprintf(file, "%s\n", argv[3]);
    if(argc>4&&strcmp("-c",argv[6])==0) {fprintf(file, ":commit_id: %s\n", argv[7]);}
    else if(argc>4&&strcmp("-c",argv[4])==0) {fprintf(file, ":commit_id: %s\n", argv[5]);}
    else {fprintf(file, ":commit_id: %d\n", find_last_commit_ID());}
    FILE *file1 = fopen(".neogit/config", "r");
    if (file1 == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    char a[100];
    while (fgets(line, sizeof(line), file1) != NULL) {
        if (strncmp(line, "username: ", 10) == 0) {
            sscanf(line, "username: %s\n", &a);
            fprintf(file, ":username: %s\n",a);
            break;            
        } 
    }
    fclose(file1);
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    fprintf(file, ":time: %s\n", asctime(localTime));
    if(argc>4&&strcmp("-m",argv[4])==0){
        char message[72];
        strcpy(message,argv[5]);
        fclose(file1);
    }
    fclose(file);
    return 0;
}
bool is_taged(char tag_name[]){
    FILE *file = fopen(".neogit/tags", "r");
    if (file == NULL) return false;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(line, tag_name) == 0) return true;
    }
    fclose(file); 
    return false;
}
int remove_tag(char tag_name[]){
    FILE *file = fopen(".neogit/tags", "r");
    if (file == NULL) return 1;
    FILE *tmp_file = fopen("tmp_tags", "w");
    char line[MAX_LINE_LENGTH];
    int check1=0,check2=1;
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if(check1&&line[0]!=':'){check2=1;}   
        if(strcmp(line,tag_name)==0&&check2){
            check1=1;
            check2=0;
        }
        if (check2){
            fprintf(tmp_file, "%s\n", line);
        }
    }
    fclose(file);
    fclose(tmp_file);
    remove(".neogit/tags");
    rename("tmp_tags", ".neogit/tags");
    return 0;
}
int run_diff(int argc, char * const argv[]){
    if(strcmp(argv[2],"-c")==0) return run_diff_c(atoi(argv[3]),atoi(argv[4]));
    if(strcmp(argv[2],"-f")==0) {
        if(argc==5) return run_diff_f(argv[3],1,tedede_khotoot(argv[3]),argv[4],1,tedede_khotoot(argv[4]));
        if(argc==7){
            if(strcmp(argv[5],"-line1")==0){
                int beggin,end;
                sscanf(argv[6],"%d-%d",&beggin,&end);
                return run_diff_f(argv[3],beggin,end,argv[4],1,tedede_khotoot(argv[4]));                
            }
            if(strcmp(argv[5],"-line2")==0){
                int beggin,end;
                sscanf(argv[6],"%d-%d",&beggin,&end);
                return run_diff_f(argv[3],1,tedede_khotoot(argv[3]),argv[4],beggin,end);                
            }
            return 1;
        }
        if(argc==9){
            int beggin1,end1,beggin2,end2;
            sscanf(argv[6],"%d-%d",&beggin1,&end1);
            sscanf(argv[8],"%d-%d",&beggin2,&end2);
            return run_diff_f(argv[3],beggin1,end1,argv[4],beggin2,end2);
        } 
        return 1;
    }
}
int run_diff_f(char filename1[],int beggin1,int end1,char filename2[],int beggin2,int end2){
    if(end1>tedede_khotoot(filename1)) {end1=tedede_khotoot(filename1);}
    if(end2>tedede_khotoot(filename2)) {end2=tedede_khotoot(filename2);}
    FILE*file1=fopen(filename1,"r");
    FILE*file2=fopen(filename2,"r");
    char line1[MAX_LINE_LENGTH],line2[MAX_LINE_LENGTH];
    int i=0,j=0;
    while (fgets(line1, sizeof(line1), file1) != NULL){
        i++;
        if(i==beggin1) {break;}
    }
    while (fgets(line2, sizeof(line2), file2) != NULL){
        j++;
        if(j==beggin2) {break;}
    }
    while(1){
        while(line1[0]=='\n'){
            if(fgets(line1, sizeof(line1), file1) == NULL) {return 0;}
            i++;
        }
        remove_spase(line1);
        while(line2[0]=='\n'){
            if(fgets(line2, sizeof(line2), file2) == NULL) {return 0;}
            j++;
        }
        remove_spase(line2);
        if(strcmp(line1,line2)!=0){
            printf("«««««\n");
            printf("%s-%d\n",filename1,i);
            puts(line1);
            printf("%s-%d\n",filename2,j);
            puts(line2);
            printf("»»»»»\n");
        }
        if(fgets(line1, sizeof(line1), file1) == NULL&&fgets(line2, sizeof(line2), file2) == NULL){
            fclose(file1),fclose(file2);
            return 0;
        }
        i++,j++;
        if(i==end1||j==end2){
            fclose(file1),fclose(file2);
            return 0;
        }
    }
}
int run_diff_c(int commit_id1,int commit_id2){
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commit_id1);
    strcat(commit_filepath, tmp);
    FILE *file = fopen(commit_filepath, "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    int check=0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if(check){
        if(!is_commited(line,commit_id2))
        printf("%s is commited in %d but not comitted in %d\n",line,commit_id1,commit_id2);
        }
        if (strcmp(line, "files:") == 0&&!check) {
            check=1;       
        } 
    }
    fclose(file);
    char commit_filepath2[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath2, ".neogit/commits/");
    char tmp2[10];
    sprintf(tmp2, "%d", commit_id2);
    strcat(commit_filepath2, tmp2);
    file = fopen(commit_filepath2, "r");
    if (file == NULL) return 1;
    check=0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if(check){
        if(!is_commited(line,commit_id1))
        printf("%s is commited in %d but not comitted in %d\n",line,commit_id2,commit_id1);
        }
        if (strcmp(line, "files:") == 0&&!check) {
            check=1;       
        } 
    }
    rewind(file);
    check=0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if(check){
        if(is_commited(line,commit_id1)){
            char filename1[80],filename2[80];
            strcpy(filename1, ".neogit/commits/");
            char tmp3[10];
            sprintf(tmp3, "%d", commit_id1);
            strcat(filename1, tmp3);
            strcpy(filename2, ".neogit/commits/");
            char tmp4[10];
            sprintf(tmp3, "%d", commit_id2);
            strcat(filename2, tmp4);
            if(run_diff_f(filename1,0,tedede_khotoot(filename1),filename2,0,tedede_khotoot(filename2)))
            return 1;
        }
        }
        if (strcmp(line, "files:") == 0&&!check) {
            check=1;       
        } 
    }
    fclose(file);
    return 0;
}
bool is_commited(char *filepath,int commite_id) {
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, ".neogit/commits/");
    char tmp[10];
    sprintf(tmp, "%d", commite_id);
    strcat(commit_filepath, tmp);
    strcat(filepath, " ");
    FILE *file = fopen(commit_filepath, "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strncmp(line, filepath,strlen(filepath)) == 0) return true;
    }
    fclose(file); 
    return false;
}
bool is_count(char *string) {
    for(int i=0;i<strlen(string);i++) {
        if (!isdigit(string[i])) return  false;
    }
    return true;
}
int tedede_khotoot(char filename []){
    FILE *file;
    char line[100];
    int lineCount = 0;
    file = fopen(filename, "r");
    if (file == NULL) 
        return 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        lineCount++;
    }
    fclose(file);
    return lineCount;
}
int teedade_kaleme(char a[]){
    int count=0;
    for(int i=0;i<strlen(a);i++)
    if(a[i]==' ')
    count++;
    return count;
}
void remove_spase(char line[]){
    while (line[0]==' '||line[0]=='\t')
    {strcpy(line,line+1);}
    while (line[strlen(line)-1]==' '||line[strlen(line)-1]=='\t')
    {strcpy(line+strlen(line)-1,line+strlen(line));}  
    for(int i=0;i<strlen(line);i++){
        if(line[i]==' '&&line[i+1]==' '){
            strcpy(line+i,line+i+1);
        }
    }  
}
//