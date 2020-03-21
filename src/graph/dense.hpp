//    Copyright 2019 Jij Inc.

//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at

//        http://www.apache.org/licenses/LICENSE-2.0

//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#ifndef OPENJIJ_GRAPH_DENSE_HPP__
#define OPENJIJ_GRAPH_DENSE_HPP__

#include <map>
#include <vector>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <algorithm>

#include <graph/graph.hpp>
#include <graph/bqm/binary_quadratic_model.hpp>

namespace openjij {
    namespace graph {

        /**
         * @brief two-body all-to-all interactions 
         *
         * @tparam FloatType float type of Sparse class (double or float)
         */
        template<typename FloatType>
            class Dense : public Graph{
                static_assert(std::is_floating_point<FloatType>::value, "FloatType must be floating-point type.");
                public:

                    /**
                     * @brief interaction type
                     */
                    using Interactions = BinaryQuadraticModel<Index, FloatType>;

                    /**
                     * @brief float type
                     */
                    using value_type = FloatType;
                    
                private:

                    /**
                     * @brief interactions (the number of intereactions is num_spins*(num_spins+1)/2) 
                     */
                    Interactions _J;

                public:

                    /**
                     * @brief Dense constructor
                     *
                     * @param num_spins the number of spins
                     */
                    explicit Dense(const BinaryQuadraticModel<Index, FloatType> &bqm)
                        : Graph(bqm.length()), _J(bqm){
                        }

                    explicit Dense(const std::size_t num_spins)
                        : Graph(num_spins), _J({}, {}, 0.0, Vartype::SPIN, ""){

                        }

                    /**
                     * @brief Dense copy constructor
                     */
                    Dense(const Dense<FloatType>&) = default;

                    /**
                     * @brief Dense move constructor
                     */
                    Dense(Dense<FloatType>&&) = default;

                    /**
                     * @brief returns list of adjacent nodes 
                     *
                     * @param ind Node index
                     *
                     * @return list of adjacent nodes
                     */
                    const Nodes& adj_nodes(Index ind) const{
                        return _list_adj_nodes[ind];
                    }

                    //DEPRECATED
                    //TODO: calc_energy should not be the member function.

                    /**
                     * @brief calculate total energy 
                     *
                     * @param spins
                     *
                     * @return corresponding energy
                     */
                    FloatType calc_energy(const Spins& spins) const{
                        Sample<Index> sample;
                        Index ind = 0;
                        for(auto ind = 0; ind < _num_spins; ++ind)
                        {
                            insert_or_assign(sample, ind, spins[ind]);
                        }
                        FloatType ret = _J.energy(sample);
                        return ret;
                    }

                    /**
                     * @brief access J_{ij}
                     *
                     * @param i Index i
                     * @param j Index j
                     *
                     * @return J_{ij}
                     */
                    FloatType& J(Index i, Index j){
                        assert(i < get_num_spins());
                        assert(j < get_num_spins());
                        auto& quadratic = _J.get_quadratic();
                        if(quadratic.count(std::make_pair(i, j))==0)
                        {
                            _J.add_interaction(i, j, 0.0, Vartype::SPIN);
                        }
                        return quadratic[std::make_pair(i, j)];
                    }

                    /**
                     * @brief access J_{ij}
                     *
                     * @param i Index i
                     * @param j Index j
                     *
                     * @return J_{ij}
                     */
                    const FloatType& J(Index i, Index j) const{
                        assert(i < get_num_spins());
                        assert(j < get_num_spins());
                        auto& quadratic = _J.get_quadratic();
                        return quadratic[std::make_pair(i, j)];
                    }

                    /**
                     * @brief access h_{i} (local field)
                     *
                     * @param i Index i
                     *
                     * @return h_{i}
                     */
                    FloatType& h(Index i){
                        assert(i < get_num_spins());
                        //add node if it does not exist
                        auto& linear = _J.get_linear();
                        if(linear.count(i)==0)
                        {
                            _J.add_variable(i, 0.0, Vartype::SPIN);
                        }
                        return linear[i];
                    }

                    /**
                     * @brief access h_{i} (local field)
                     *
                     * @param i Index i
                     *
                     * @return h_{i}
                     */
                    const FloatType& h(Index i) const{
                        assert(i < get_num_spins());
                        auto& linear = _J.get_linear();
                        return linear[i];
                    }

            };
    } // namespace graph 
} // namespace openjij

#endif
