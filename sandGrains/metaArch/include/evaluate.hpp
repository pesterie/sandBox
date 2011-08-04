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
#ifndef EVALUATE_HPP_INCLUDED
#define EVALUATE_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <cassert>
#include <vector>
#include <boost/static_assert.hpp>

struct  evaluate_;


/*******************************************************************************
 * Evaluator for vector terminals
 ******************************************************************************/
struct fetch_vector : boost::proto::callable
{
  template<typename Sig> struct result;

  template<typename This,typename Expr,typename Int>
  struct result<This(Expr, Int)>
  {
    typedef typename boost::proto::result_of::value<Expr>::type base;
    typedef typename boost::remove_reference<base>::type vec;
    typedef typename boost::mpl::if_< boost::is_reference<base>, 
                                      typename vec::reference, 
                                      typename vec::value_type
                                    >::type type;
  };

  template<typename Expr> inline
  typename result<fetch_vector(Expr &, int)>::type 
  operator()(Expr & expr, int i) const
  {
    return boost::proto::value(expr)[i];
  }
};


/*******************************************************************************
 * Switch based evaluate_ cases
 ******************************************************************************/
struct  evaluate_cases
{
  // The primary template goes for the _default:
  template<typename Tag>
  struct case_ : boost::proto::_default<evaluate_> {};
};

/*******************************************************************************
 * Switch based Grammar
 ******************************************************************************/
struct  evaluate_ : boost::proto::switch_< evaluate_cases > {};

/*******************************************************************************
 * Switch based Grammar - Constant case
 * We use more refined if_ and and_ to check any type convertible to double
 ******************************************************************************/
template<>
struct    evaluate_cases
        ::case_<boost::proto::tag::terminal>
        : boost::proto::when
          < boost::proto::terminal< boost::proto::_>
          , boost::proto::_value
          >
{};

#endif
