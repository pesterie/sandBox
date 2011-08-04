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
#ifndef TERMINALS_HPP_INCLUDED
#define TERMINALS_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <vector>
#include <iostream>
#include <grammar.hpp>
#include <expression.hpp>
#include <evaluate.hpp>
#include <size.hpp>

/*******************************************************************************
 * std vector terminals 
 ******************************************************************************/
struct vector_tag {};

template<>
struct    vector_function_cases
        ::case_< vector_tag >
        : boost::proto::nullary_expr< vector_tag, boost::proto::_ >
{};

/*******************************************************************************
 * Switch based Transform - Vector case
 ******************************************************************************/
template<>
struct    evaluate_cases
        ::case_< vector_tag >
        : boost::proto::when
          < boost::proto::nullary_expr< vector_tag, boost::proto::_ >
            , fetch_vector(boost::proto::_, boost::proto::_state)
          > 
{};

/*******************************************************************************
 * User class
 ******************************************************************************/
template<typename T>
struct vector 
  : vector_expression< typename boost::proto::nullary_expr<vector_tag, std::vector<T> >::type >
{
  typedef typename boost::proto::nullary_expr<vector_tag, std::vector<T> >::type expr_type;
  typedef typename std::vector<T> value_type;

  vector(std::size_t size = 0, T const& value = T() )
    : vector_expression< expr_type >(expr_type::make(std::vector<T>(size,value)))
  {}

  typedef std::vector<T> result_type;

  //EVALUATION
  template<typename Expr>
  vector& operator=(Expr const& expr)
  {
    evaluate_ callee;
    size_ get_size;
    size_t size = get_size(expr);
    for(int i = 0; i != size; ++i)
      callee(boost::proto::make_expr<boost::proto::tag::assign>(boost::ref(*this), boost::cref(expr)), i);
    return *this;
  }

};


template<typename T>
std::ostream& operator<<(std::ostream &out, vector<T> const& v)
{
  std::size_t size = boost::proto::value(v).size();
  for(std::size_t i = 0; i < size; ++i)
  {
    out << boost::proto::value(v)[i] << " ";
  }
  out << "\n";
  return out; 
}

#endif
