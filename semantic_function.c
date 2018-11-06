#include <stdio.h>
#include "semantic.h"
#include "ast.h"

void ast_check_semantics() {
	if (ast == NULL) {
		errorOccurred = 1;
		fprintf(errorFile, "Main scope not found.\n");
		return;
	}
	else {
		ast_traverse(ast, 0, &ast_scope_generator, &ast_sementic_check);

	}

}
void ast_scope_generator(node *cur, int x) { //Done pre-post.

	if (cur->kind == SCOPE_NODE) {
		scope_enter();
	}
}
//checking function and function arguments

void ast_sementic_check(node* current, int x) {

	if (current == NULL) {
		errorOccurred = 1;
		fprintf(errorFile, "Error: Empty tree visited");
		return;
	}
	node_kind kind = current->kind;

	switch (kind) {
		case UNKNOWN: {break;}
		case SCOPE_NODE: {scope_exit();	fprintf(errorFile,"Reached scope\n");break;}
		case DECLARATIONS_NODE: {fprintf(errorFile,"Reached declarations node\n");break; } //break
		case STATEMENTS_NODE: {fprintf(errorFile,"Reached statements node\n");break;} //break
		case UNARY_EXPRESION_NODE: {
		fprintf(errorFile,"Reached unary");		
		break;} 
		case BINARY_EXPRESSION_NODE: {
			fprintf(errorFile,"Reached binary node\n");
			int left = current->binary_expr.left->type.type_code;
			int right = current->binary_expr.right->type.type_code;
			int op = current->binary_expr.op;

			fprintf(errorFile,"Type codes of binary expression Val left:%d Val right:%d\n",left,right);

			if (op == EQ ){
				if (left == right){
					current->type.type_code = BOOL_T;
					current->type.vec = 1;
					fprintf(errorFile,"Assigning type code of boolean: %d\n",current->type.type_code);
					break;//this wasn't there before and was causing problems!!! remember to break!!!
				}	
				else{
					fprintf(errorFile,"Error: Expecting same type on both sides\n");
					//current->type.type_code = -1;
					break;
				}
			}
		}
			
		case INT_NODE:{
			fprintf(errorFile,"Reached int node\n");
			current->type.type_code = INT_T;
			current->type.vec = 1;
			current->type.is_const = 1;
			break;}
		case FLOAT_NODE:{
			fprintf(errorFile,"Reached float node\n");
			current->type.type_code = FLOAT_T;
			current->type.vec = 1;
			current->type.is_const = 1;
			break; }
		case VAR_NODE:{fprintf(errorFile,"Reached var\n");}
		case FUNCTION_NODE:{
			//pointer to the arguments of the function
			node* next_arg = current->func.args;

			//if no arguments, return error
			if (current->func.args == NULL){
				fprintf(errorFile, "Error: must have arguments, cannot be void\n");
				break;
			}

			//get next arguments
			next_arg = next_arg->args.args;
	
			//current->type.type_code will be the return type of the function
			if (current->func.name == 2) { //rsq
				fprintf(errorFile,"Type of args:%d \n",next_arg->type.type_code);
				if (!(next_arg->type.type_code == FLOAT_T ||next_arg->type.type_code == INT_T )) {
					fprintf(errorFile,"Error: Expecting float or integer for first argument\n");
					break;
				}
				
				next_arg = next_arg->args.args;
				if (next_arg != NULL){
					fprintf(errorFile,"Error: Too many arguments for this function\n");					
				}

			}

	
			else if (current->func.name == 0) { //dp3

				//case:vec4
				if (next_arg == NULL){
					fprintf(errorFile, "Input argument cannot be void\n");	
					break;
				}
				if (!(next_arg->type.type_code == VEC_T && next_arg->type.vec == 4)){
					fprintf(errorFile, "First argument is of incorrect type\n");	
					break;
				}
				else if (next_arg->type.type_code == VEC_T && next_arg->type.vec == 4){
					next_arg = next_arg->args.args;
					if (next_arg == NULL){
						fprintf(errorFile, "Input argument cannot be void\n");	
						break;
					}
					if (!(next_arg->type.type_code == VEC_T && next_arg->type.vec == 4)) {
						fprintf(errorFile, "Second argument is of incorrect type\n");	
						break;
					}
	
				}
		
				//other vector type case:vec3
				if (next_arg == NULL){
					fprintf(errorFile, "Input argument cannot be void\n");		
					break;
				}
				if (!(next_arg->type.type_code == VEC_T && next_arg->type.vec == 3)){
					fprintf(errorFile, "First argument is of incorrect type\n");		
					break;
				}
				else if (next_arg->type.type_code == VEC_T && next_arg->type.vec == 3){
					next_arg = next_arg->args.args;
					if (next_arg == NULL){
						fprintf(errorFile, "Input argument cannot be void\n");	
						break;
					}
					if (!(next_arg->type.type_code == VEC_T && next_arg->type.vec == 3)) {
						fprintf(errorFile, "Second argument is of incorrect type\n");
						break;
					}
	
				}
				//other vector type case:ivec4
				if (!(next_arg->type.type_code == IVEC_T && next_arg->type.vec == 4)){
					fprintf(errorFile, "First argument is of incorrect type\n");	
					break;
				}
				else if (next_arg->type.type_code == IVEC_T && next_arg->type.vec == 4){
					next_arg = next_arg->args.args;
					if (next_arg == NULL){
						fprintf(errorFile, "Input argument cannot be void\n");
						break;
					}
					if (!(next_arg->type.type_code == IVEC_T && next_arg->type.vec == 4)) {
						fprintf(errorFile, "Second argument is of incorrect type\n");
						break;
					}
	
				}
				//last vector type case: ivec4
				if (!(next_arg->type.type_code == IVEC_T && next_arg->type.vec == 3)){
					fprintf(errorFile, "First argument is of incorrect type\n");
					break;
				}
				else if (next_arg->type.type_code == IVEC_T && next_arg->type.vec == 3){
					next_arg = next_arg->args.args;
					if (next_arg == NULL){
						fprintf(errorFile, "Input argument cannot be void\n");
						break;
					}
					if (!(next_arg->type.type_code == IVEC_T && next_arg->type.vec == 3)) {
						fprintf(errorFile, "Second argument is of incorrect type\n");
						break;
					}
	
				}
			}

			else if (current->func.name == 1) { //lit
				if (!(next_arg->type.type_code == VEC_T && next_arg->type.vec==4)) {
					fprintf(errorFile,"Error: LIT function only takes in arguments of type vec4\n");
					break;
				}
			}
			else {
				fprintf(errorFile,"Error: Function name not recognized\n");
					break;
			}
		}

		case CONSTRUCTOR_NODE: {fprintf(errorFile,"Reached construct\n");break;} 
		case ARGUMENTS_NODE:{	
			fprintf(errorFile,"Reached arguments node\n");		
			if (current->args.expr){
				//arguments must be of expected type  
				current->type.is_const = current->args.expr->type.is_const;	
				fprintf(errorFile,"Type code args: %d\n",current->args.expr->type.type_code);
				current->type.type_code = current->args.expr->type.type_code;
				current->type.vec = current->args.expr->type.vec;
				break;
			}
			else{
				current->type.is_const = 0; //verify
				current->type.type_code = -1; //verify
				current->type.vec = 1;
				break;
				
			}
		}
		case BOOL_NODE:{
			fprintf(errorFile,"Reached bool node\n");
			current->type.type_code = BOOL_T;
			current->type.vec = 1;
			current->type.is_const = 1;
			break;}
		case IF_STATEMENT_NODE:{
			fprintf(errorFile,"Reached if condition\n");		
			fprintf(errorFile,"Type code of conditional expression: %d\n",current->if_stmt.condition_expr->type.type_code);
			if (!(current->if_stmt.condition_expr->type.type_code == BOOL_T && current->if_stmt.condition_expr->type.vec == 1)){ //can't be bvec
				fprintf(errorFile, "Error: conditional expression must be of type boolean\n");	
				break;		
			}
		}
		case ASSIGNMENT_NODE:{fprintf(errorFile,"Reached assignment\n");break;}
		case NESTED_SCOPE_NODE: {fprintf(errorFile,"Reached nested_scope\n");break;} //TODO
		case NESTED_EXPRESSION_NODE: {
			fprintf(errorFile,"Reached nested_exp node\n");
			current->type.is_const = current->nested_expr.expr->type.is_const;
		 	current->type.type_code = current->nested_expr.expr->type.type_code;
			fprintf(errorFile,"Type code nested: %d\n",current->type.type_code);
			current->type.vec = current->nested_expr.expr->type.vec;
			
		} 
		case EXP_VAR_NODE: {
			fprintf(errorFile,"Reached exp_var node\n");
			current->type.is_const = current->exp_var_node.var_node->type.is_const;
		  	current->type.type_code = current->exp_var_node.var_node->type.type_code;
			fprintf(errorFile,"Type code exp_var: %d\n",current->type.type_code);
			current->type.vec = current->exp_var_node.var_node->type.vec; 
			break; }
		case DECLARATION_NODE:{		
			fprintf(errorFile,"Reached declaration\n");		
			symbol_table_entry new_entry;

			new_entry.id = current->declaration.id;
			new_entry.is_const = current->declaration.is_const;
			new_entry.type_code = current->declaration.type_node->type.type_code;
			new_entry.vec = current->declaration.type_node->type.vec;

			//if initialized
			new_entry.is_init = 1;

			symbol_add(new_entry);
		 	break;}
		default: {break;}
	}
	
}
  

