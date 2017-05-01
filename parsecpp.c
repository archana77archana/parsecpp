#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>

/* The following is the size of a buffer to contain any error messages
   encountered when the regular expression is compiled. */

#define MAX_ERROR_MSG 0x1000

/* Compile the regular expression described by "regex_text" into
   "r". */

static int compile_regex (regex_t *r, const char *regex_text) {
    int status = regcomp (r, regex_text, REG_EXTENDED|REG_NEWLINE);
    if (status != 0) {
	char error_message[MAX_ERROR_MSG];
	regerror (status, r, error_message, MAX_ERROR_MSG);
        printf ("Regex error compiling '%s': %s\n", regex_text, error_message);
        return 1;
    }
    return 0;
}

void table_entries(FILE *file, const char *contents, int start) {
    // table processing
    int loop;
    // row
    fprintf(file, "<tr>");
            
    for(loop = start; contents[loop] != '('; loop++);
    loop++;
            
    for(; contents[loop] != ')'; loop++) {
        fprintf(file, "<td>");
        
        // removing ""
        if(contents[loop] == '"') {
                loop++;
        }
        
        while((contents[loop] != ',') && (contents[loop] != ')')) {
            fprintf(file, "%c", contents[loop]);
            loop++;
            if(contents[loop] == '"') {
                loop++;
            }
        }
              
        if(contents[loop] == ')')
            break;
              
        loop++;
        fprintf(file, "</td>");
    }
            
    fprintf(file,"</tr>");   
}

/*
  Match the string in "contents" against the compiled regular
  expression in "r".
 */

static int match_regex (regex_t * r, const char * contents, FILE *file) {
    /* "P" is a pointer into the string which points to the end of the
       previous match. */
    const char * p = contents;
    /* "N_matches" is the maximum number of matches allowed. */
    const int n_matches = 10;
    /* "M" contains the matches found. */
    regmatch_t m[n_matches];

    while (1) {
        int i = 0;
        int nomatch = regexec (r, p, n_matches, m, 0);
        if (nomatch) {
            printf ("No more matches.\n");
            return nomatch;
        }
        for (i = 0; i < n_matches; i++) {
            int start;
            int finish;
            if (m[i].rm_so == -1) {
                break;
            }
            start = m[i].rm_so + (p - contents);
            finish = m[i].rm_eo + (p - contents);
            if (i == 0) {
                printf ("$& is ");
            }
            else {
                printf ("$%d is ", i);
            }
            printf ("'%.*s' (bytes %d:%d)\n", (finish - start), contents + start, start, finish);
            
            //table entries
            table_entries(file, contents, start);
        }
        p += m[0].rm_eo;
    }
    return 0;
}

int main (int argc, char **argv)
{
    // file variables
    char *input = argv[1];
    FILE *input_file;
    long input_file_size;
    char *file_contents;

    // html file variables
    FILE *html_file;
    html_file = fopen("student_details.html", "w");

    input_file = fopen(input, "rb");
    fseek(input_file, 0, SEEK_END);
    // read file contents into a variable
    input_file_size = ftell(input_file);
    rewind(input_file);
    file_contents = malloc(input_file_size * (sizeof(char)));
    fread(file_contents, sizeof(char), input_file_size, input_file);

    //regular expression variables
    regex_t r;
    const char * regex_text; // text to search to find out the object initializations in the cpp file
    regex_text = "    student_details ";

    // writing the html file
    fprintf(html_file, "<!DOCTYPE html><html><head><style>table, th, td {"
                        "border: 1px solid black;"
                        "border-collapse: collapse;}th, td {padding: 5px;}th {text-align: left;}</style></head><body>");
    fprintf(html_file, "<p><button  onclick=\"sortTable()\">Sort alphabetically</button></p>");
    fprintf(html_file, "<table id=\"student_details\" style=\"text-align:center; border: 1px solid\"><th>Department&nbsp;&nbsp;</th>"
		"<th>Register Number&nbsp;&nbsp;</th><th>Name&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</th><th>SSLC Marks&nbsp;&nbsp;&nbsp;&nbsp;</th><th>HSc Marks&nbsp;&nbsp;&nbsp;&nbsp;</th><th>UG-Marks&nbsp;&nbsp;</th><th>PG-Marks&nbsp;&nbsp;</th>");

    compile_regex (& r, regex_text);
    match_regex (& r, file_contents, html_file);
    
    printf("HTML created as student_details.html in the same folder.");

    fprintf(html_file, "</table><script src=\"student_details.js\" type=\"text/javascript\"></script></body></html>");
    regfree (& r);
    
    // debug
    //printf("File contents: %s", file_contents);

    // if no input given
    if (input_file == 0)
    {
        //fopen returns 0, the NULL pointer, on failure
        perror("Cannot open input file\n");
        exit(-1);
    }

    fclose(input_file);
    fclose(html_file);

    printf("\n");

    return 0;
}