#!/usr/bin/perl
# 2016/12/26 16:19:06 david
#

$decls = $incls = '';

open NODES, "find ast -name \\*.h -print | sed -e 's=ast/==g' | "
  or die "Could not list node headers";
while (<NODES>) {
  if (m/\ball\.h\b/) { next; }
  chomp;
  $decl = $incl = $_;
  #
  # Handle declaration
  #
  $i = $decl =~ s-(([[:alnum:]]|_)+)/-namespace $1 { -g;
  $decl =~ s-(([[:alnum:]]|_)+?)\.h-class $1; -;
  $decls .= $decl;
  for ($j = 0; $j < $i; $j++) {
    $decls .= "} ";
  }
  $decls .= "\n";
  #
  # Handle include
  #
  $incl =~ s=^=#include "ast/=;
  $incl =~ s/$/"/;
  $incls .= "$incl\n";
}
close NODES;

###########################################################################
#
# File "nodes/all.h" will now be produced.
#
print<<__EOF__;
//
// **** AUTOMATICALLY GENERATED BY mknodedecls.pl -- DO NOT EDIT ****
//
#ifdef __NODE_DECLARATIONS_ONLY__

//---------------------------------------------------------------------------
//     THESE ARE PREDEFINED NODES, AVAILABLE FROM THE CDK
//---------------------------------------------------------------------------

namespace cdk {
  class basic_node; class nil_node; class data_node;
  class sequence_node; class expression_node;
  template <typename StoredType> class literal_node;
  class double_node; class integer_node; class string_node;
  class unary_expression_node; 
  class neg_node; class not_node;
  class binary_expression_node;
  class add_node;   class sub_node; class mul_node; class div_node;
  class mod_node;   class lt_node;  class le_node;  class ge_node;  
  class gt_node;    class eq_node;  class ne_node; 
  class and_node; class or_node;
  class lvalue_node; class identifier_node;
  class rvalue_node; class assignment_node;
} // namespace cdk

//---------------------------------------------------------------------------
//     THESE ARE THE NODES DEFINED SPECIFICALLY FOR THIS APPLICATION
//---------------------------------------------------------------------------

namespace ook {
$decls
} // namespace ook

//---------------------------------------------------------------------------
//     A L I A S E S
//---------------------------------------------------------------------------

#else /* !defined(__NODE_DECLARATIONS_ONLY__) */

#ifndef __AUTOMATIC_NODE_ALLNODES_H__
#define __AUTOMATIC_NODE_ALLNODES_H__

//---------------------------------------------------------------------------
//     THESE ARE PREDEFINED NODES, AVAILABLE FROM THE CDK
//---------------------------------------------------------------------------

#include <cdk/ast/data_node.h>
#include <cdk/ast/nil_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/integer_node.h>
#include <cdk/ast/double_node.h>
#include <cdk/ast/string_node.h>
#include <cdk/ast/neg_node.h>
#include <cdk/ast/not_node.h>
#include <cdk/ast/add_node.h>
#include <cdk/ast/sub_node.h>
#include <cdk/ast/mul_node.h>
#include <cdk/ast/div_node.h>
#include <cdk/ast/mod_node.h>
#include <cdk/ast/lt_node.h>
#include <cdk/ast/gt_node.h>
#include <cdk/ast/ge_node.h>
#include <cdk/ast/le_node.h>
#include <cdk/ast/ne_node.h>
#include <cdk/ast/eq_node.h>
#include <cdk/ast/and_node.h>
#include <cdk/ast/or_node.h>
#include <cdk/ast/identifier_node.h>
#include <cdk/ast/rvalue_node.h>
#include <cdk/ast/assignment_node.h>

//---------------------------------------------------------------------------
//     THESE ARE THE NODES DEFINED SPECIFICALLY FOR THIS APPLICATION
//---------------------------------------------------------------------------

$incls

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------

#endif /* !defined(__AUTOMATIC_NODE_ALLNODES_H__) */

#endif /* !defined(__NODE_DECLARATIONS_ONLY__) */
__EOF__

###########################################################################

0;

###########################################################################
