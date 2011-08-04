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
#ifndef SIZE_HPP_INCLUDED
#define SIZE_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <boost/static_assert.hpp>
#include <expression.hpp>
#include <terminals.hpp>
#include <boost/mpl/equal_to.hpp>

struct fetch_container_size : boost::proto::callable
{
  template<typename Sig> struct result;

  template<typename This,typename Left, typename Right>
  struct result<This(Left,Right)>
  {
    typedef typename boost::proto::result_of::value<Left>::type   vec_0;
    typedef typename boost::proto::result_of::value<Right>::type  vec_1;
    typedef typename boost::remove_reference<vec_0>::type         base_0;
    typedef typename boost::remove_reference<vec_1>::type         base_1;
    typedef typename base_0::size_type                            size_t_0;
    typedef typename base_1::size_type                            size_t_1;
    BOOST_STATIC_ASSERT((boost::is_same< size_t_0, size_t_1>::value));
    BOOST_STATIC_ASSERT((boost::is_same< size_t_0, std::size_t>::value));
    typedef size_t_0 type;
  };

  template<typename Left, typename Right> inline
  typename result<fetch_container_size(Left,Right)>::type 
  operator()(Left & left, Right & right) const
  {
    const std::size_t size_0 = boost::proto::value(left).size();
    const std::size_t size_1 = boost::proto::value(right).size();
    assert(size_0 == size_1);
    return size_0;
  }

};

struct size_cases
{
  template<typename Tag>
  struct case_ : boost::proto::when< 
                                     boost::proto::binary_expr< 
                                                                boost::proto::_
                                                              , boost::proto::_
                                                              , boost::proto::_
                                                              >
    , fetch_container_size(boost::proto::_child_c<0>,boost::proto::_child_c<1>)
                                   > 
  {};
};

struct size_ : boost::proto::switch_<size_cases> {};



#endif /* SIZE_HPP_INCLUDED */
