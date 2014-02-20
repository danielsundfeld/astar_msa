/* Boost.MultiIndex basic example.
 *
 * Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#if !defined(NDEBUG)
#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#define BOOST_MULTI_INDEX_ENABLE_SAFE_MODE
#endif

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#include "AStar.h"
#include "HeuristicHPair.h"
#include "read_fasta.h"

using boost::multi_index_container;
using namespace boost::multi_index;

/* an employee record holds its ID, name and age */

struct employee
{
  int         id;
  std::string name;
  int         age;

  employee(int id_,std::string name_,int age_):id(id_),name(name_),age(age_){}

  friend std::ostream& operator<<(std::ostream& os,const employee& e)
  {
    os<<e.id<<" "<<e.name<<" "<<e.age<<std::endl;
    return os;
  }
};

/* tags for accessing the corresponding indices of employee_set */

struct id{};
struct name{};
struct age{};

/* see Compiler specifics: Use of member_offset for info on
 * BOOST_MULTI_INDEX_MEMBER
 */

/* Define a multi_index_container of employees with following indices:
 *   - a unique index sorted by employee::int,
 *   - a non-unique index sorted by employee::name,
 *   - a non-unique index sorted by employee::age.
 */

typedef multi_index_container<
  employee,
  indexed_by<
    ordered_unique<
      tag<id>,  BOOST_MULTI_INDEX_MEMBER(employee,int,id)>,
    ordered_non_unique<
      tag<name>,BOOST_MULTI_INDEX_MEMBER(employee,std::string,name)>,
    ordered_non_unique<
      tag<age>, BOOST_MULTI_INDEX_MEMBER(employee,int,age)> >
> employee_set;
template<typename Tag,typename MultiIndexContainer>
void print_out_by(
 const MultiIndexContainer& s,
 Tag* =0 /* fixes a MSVC++ 6.0 bug with implicit template function parms */
)
{
  /* obtain a reference to the index tagged by Tag */

  const typename boost::multi_index::index<MultiIndexContainer,Tag>::type& i=
    get<Tag>(s);

  typedef typename MultiIndexContainer::value_type value_type;

  /* dump the elements of the index to cout */
  for (auto it = i.begin(); it != i.end(); it++)
  {
        std::cout << *it << endl;
  }
  //std::copy(i.begin(),i.end(),std::ostream_iterator<value_type>(std::cout));
}


/********************************************************************/
struct pos{};
struct priority{};

typedef multi_index_container<
  Node,
  indexed_by<
    ordered_unique<
      tag<pos>,  BOOST_MULTI_INDEX_MEMBER(Node,Coord,pos)>,
    ordered_non_unique<
      tag<priority>, BOOST_MULTI_INDEX_MEMBER(Node,int,m_f)> >
> node_set;

    node_set ClosedList;
    Node current;


void add_to_closed_list(Node &father, const Coord &son)
{
    vector<Node> neigh;

    father.getNeigh(neigh);

    for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        if ((*it).pos == son)
        {
            ClosedList.insert(*it);
            father = *it;
            return;
        }
}

void test_init(vector< string > &a)
{
    Sequences *seq = Sequences::getInstance();
    seq->set_seq("CCCC");
    seq->set_seq("CCCC");
    seq->set_seq("CCCC");

    HeuristicHPair::getInstance()->init();
    Coord c = Sequences::get_initial_coord();
    const Node node_zero = Sequences::get_initial_node();
    ClosedList.insert(node_zero);
    current = node_zero;
}

void test_end()
{
    Sequences::destroyInstance();
    HeuristicHPair::destroyInstance();
}


node_set::const_iterator find(const Coord &c)
{
    return get<pos>(ClosedList).find(c);
}

node_set::const_iterator end()
{
    return ClosedList.end();
}

node_set::size_type erase(const Coord &c)
{
    return ClosedList.erase(c);
}


bool empty()
{
    return ClosedList.empty();
}

void dequeue(Node &n)
{
    auto it = get<priority>(ClosedList).begin();
    n = *it;
    ClosedList.erase(it->pos);
}

bool enqueue(const Node &c)
{
    node_set::index<pos>::type::iterator it = ClosedList.find(c.pos);
    if (it == ClosedList.end())
        return ClosedList.insert(c).second;
    return ClosedList.modify(it, change_node(c.get_f(), c.get_g(), c.get_parenti()));
}

int run_test1(void)
{
    vector< string > a;
    test_init(a);

    add_to_closed_list(current, Coord(1, 1, 1));
    add_to_closed_list(current, Coord(2, 2, 2));
    add_to_closed_list(current, Coord(3, 3, 3));

    cout << "Ok2   " << ClosedList.insert(Node(0, Coord(3, 3, 3), 7)).second << endl;
    cout << "Ok2   " << ClosedList.insert(Node(0, Coord(4, 4, 4), 7)).second << endl;

    node_set::const_iterator it = find(Coord(2,2,2));
    cout << "1- " << *it << endl;
    enqueue(Node(0, Coord(2, 2, 2), 7));
    it = find(Coord(2,2,2));
    cout << "2- " << *it << endl;

    print_out_by<priority>(ClosedList);
    cout << "--------" << endl;
    Node n;
    dequeue(n);
    print_out_by<priority>(ClosedList);
    cout << "DEQUEUD" << n << endl;

    test_end();
    return 0;
}

int main(int argc, char *argv[])
{
#if 0
    employee_set es;

    es.insert(employee(0,"Joe",31));
    es.insert(employee(1,"Robert",27));
    es.insert(employee(2,"John",40));

    /* next insertion will fail, as there is an employee with
     * the same ID
     */

    es.insert(employee(2,"Aristotle",2387));

    es.insert(employee(3,"Albert",20));
    es.insert(employee(4,"John",57));

    /* list the employees sorted by ID, name and age */

    std::cout<<"by ID"<<std::endl;
    print_out_by<id>(es);
    std::cout<<std::endl;

    std::cout<<"by name"<<std::endl;
    print_out_by<name>(es);
    std::cout<<std::endl;

    std::cout<<"by age"<<std::endl;
    print_out_by<age>(es);
    std::cout<<std::endl;
#endif
    run_test1();
    return 0;
}
