/*******************************************************************************
 *           Getting Jiggy with Boost.Proto - Boost'Con 2011 Tutorial
 *                                 by Joel Falcou
 *
 *                             Step 2 : Transformers !
 *
 *             Distributed under the Boost Software License, Version 1.0.
 *                    See accompanying file LICENSE.txt or copy at
 *                       http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <boost/array.hpp>
#include <boost/proto/proto.hpp>
#include <grammar.hpp>
#include <evaluate.hpp>

template<typename AST> struct vector_expression;

struct  vector_domain
      : boost::proto::domain< boost::proto::generator<vector_expression>
                            , vector_function
                            >
{};

template<typename AST>
struct  vector_expression
      : boost::proto::extends<AST,vector_expression<AST>,vector_domain>
{
  typedef boost::proto::
          extends<AST,vector_expression<AST>,vector_domain> extendee;

  vector_expression(AST const& ast = AST()) : extendee(ast) {}

  BOOST_PROTO_EXTENDS_USING_ASSIGN(vector_expression)
};

#endif
