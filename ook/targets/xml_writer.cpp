#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void ook::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}

void ook::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}

void ook::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}

//---------------------------------------------------------------------------

inline void ook::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

//---------------------------------------------------------------------------

inline void ook::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void ook::xml_writer::do_not_node(cdk::not_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<" << node->label() << ">" << node->name() << "</" << node->label() << ">" << std::endl;
}

void ook::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void ook::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {

  openTag(node, lvl);

  node->lvalue()->accept(this, lvl);

  node->rvalue()->accept(this, lvl + 4);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

/*void ook::xml_writer::do_program_node(ook::program_node * const node, int lvl) {
  openTag(node, lvl);
  node->statements()->accept(this, lvl + 4);
  closeTag(node, lvl);
}*/

//---------------------------------------------------------------------------

void ook::xml_writer::do_evaluation_node(ook::evaluation_node * const node, int lvl) {
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_print_node(ook::print_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_read_node(ook::read_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_while_node(ook::while_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_if_node(ook::if_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_if_else_node(ook::if_else_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_address_of_node(ook::address_of_node * const node, int lvl){
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("Value", lvl + 2);
  node->lvalue()->accept(this, lvl + 4);
  closeTag("Value", lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_alloc_node(ook::alloc_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("Positions", lvl + 2);
    node->pos()->accept(this, lvl + 4);
    closeTag("Positions", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_block_node(ook::block_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("Declarations", lvl + 2);
    if (node->declaration() != nullptr)
      node->declaration()->accept(this, lvl + 4);
    closeTag("Declarations", lvl + 2);
    openTag("Instructions", lvl + 2);
    if (node->instruction() != nullptr)
      node->instruction()->accept(this, lvl + 4);
    closeTag("Instructions", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_function_call_node(ook::function_call_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("Name", lvl + 2);
    os() << std::string(lvl +4, ' ') << *(node->name()) << std::endl;
    closeTag("Name", lvl + 2);
    openTag("Arguments", lvl + 2);
    if (node->arguments() != nullptr)
      node->arguments()->accept(this, lvl + 4);
    closeTag("Arguments", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_identity_node(ook::identity_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    closeTag(node, lvl);
}
void ook::xml_writer::do_index_node(ook::index_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("base", lvl + 2);
    node->base()->accept(this, lvl + 4);
    closeTag("base", lvl + 2);
    openTag("offset", lvl + 2);
    node->offset()->accept(this, lvl + 4);
    closeTag("offset", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_next_node(ook::next_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("Level", lvl + 2);
    os() << std::string(lvl +4, ' ') << node->n() << std::endl;
    closeTag("Level", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_null_node(ook::null_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    closeTag(node, lvl);
}
void ook::xml_writer::do_return_node(ook::return_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    closeTag(node, lvl);
}
void ook::xml_writer::do_stop_node(ook::stop_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("Level", lvl + 2);
    os() << std::string(lvl +4, ' ') << node->n() << std::endl;
    closeTag("Level", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_var_declar_node(ook::var_declar_node * const node, int lvl){
  //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("Qualifier", lvl + 2);
    if(node->pub())
        os() << std::string(lvl +4, ' ') << "public" << std::endl;
    else if (node ->impor())
        os() << std::string(lvl +4, ' ') << "import" << std::endl;
    closeTag("Qualifier", lvl + 2);
    openTag("Type", lvl + 2);
    os() << std::string(lvl +4, ' ') << node->type()->name() << std::endl;
    closeTag("Type", lvl + 2);
    
    openTag("Name", lvl + 2);
    os() << std::string(lvl +4, ' ') << *(node->name()) << std::endl;
    closeTag("Name", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_var_def_node(ook::var_def_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);

    openTag("Qualifier", lvl + 2);
    if(node->pub())
        os() << std::string(lvl +4, ' ') << "public" << std::endl;
    closeTag("Qualifier", lvl + 2);

    openTag("Type", lvl + 2);
    os() << std::string(lvl +4, ' ') << node->type()->name() << std::endl;
    closeTag("Type", lvl + 2);
    
    openTag("Name", lvl + 2);
    os() << std::string(lvl +4, ' ') << *(node->name()) << std::endl;
    closeTag("Name", lvl + 2);

    openTag("Value", lvl + 2);
    node->init()->accept(this, lvl + 4);
    closeTag("Value", lvl + 2);

    closeTag(node, lvl);
}
void ook::xml_writer::do_function_declar_node(ook::function_declar_node * const node, int lvl){
    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    openTag("Qualifier", lvl + 2);
    if(node->pub())
        os() << std::string(lvl +4, ' ') << "public" << std::endl;
    else if(node->impor())
        os() << std::string(lvl +4, ' ') << "private" << std::endl;
    closeTag("Qualifier", lvl + 2);
    openTag("Type", lvl + 2);
    os() << std::string(lvl +4, ' ') << node->type()->name() << std::endl;
    closeTag("Type", lvl + 2);

    openTag("Name", lvl + 2);
    os() << std::string(lvl +4, ' ') << *(node->name()) << std::endl;
    closeTag("Name", lvl + 2);
    openTag("Arguments", lvl + 2);
    if(!(node->arguments() == nullptr))
      node->arguments()->accept(this, lvl + 4);
    closeTag("Arguments", lvl + 2);
    closeTag(node, lvl);
}
void ook::xml_writer::do_function_def_node(ook::function_def_node * const node, int lvl){

    //ASSERT_SAFE_EXPRESSIONS;
    openTag(node, lvl);
    
    openTag("Qualifier", lvl + 2);
    if(node->pub())
        os() << std::string(lvl +4, ' ') << "public" << std::endl;
    closeTag("Qualifier", lvl + 2);

    openTag("Type", lvl + 2);
    os() << std::string(lvl +4, ' ') << node->type()->name() << std::endl;
    closeTag("Type", lvl + 2);
    
    openTag("Name", lvl + 2);
    os() << std::string(lvl +4, ' ') << *(node->name()) << std::endl;
    closeTag("Name", lvl + 2);
    
    openTag("Arguments", lvl + 2);
    if(!(node->arguments() == nullptr))
      node->arguments()->accept(this, lvl + 4);
    closeTag("Arguments", lvl + 2);
    
    openTag("Return", lvl + 2);
    if(!(node->literal() == nullptr))
      node->literal()->accept(this, lvl + 4);
    closeTag("Return", lvl + 2);
    
    openTag("Block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("Block", lvl + 2);
    

    closeTag(node, lvl);
}
