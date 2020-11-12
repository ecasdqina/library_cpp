#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>
#include <numeric>

namespace wl_kernel {
class graph_t {
public:
	struct edge_t {
		size_t u, v;

		size_t opposite(int x) { return u ^ v ^ x; }
		void swap(edge_t& r) {
			std::swap(u, r.u);
			std::swap(v, r.v);
		}
	};

protected:
	std::vector<std::vector<size_t>> graph;
	std::vector<size_t> label;
	std::vector<edge_t> edge;

public:
	graph_t(size_t n): label(n), graph(n) {}
	template<class InputIt> graph_t(InputIt first, InputIt last)
		: graph_t(std::distance(first, last)) {

		for(int i = 0; i < graph.size(); i++) {
			label[i] = *first;
			first++;
		}
	}

	void add_edge(size_t u, size_t v) {
		graph[u].push_back(v);
		graph[v].push_back(u);
		edge.push_back(edge_t{u, v});
	}

	size_t size() { return graph.size(); }
	size_t edge_size() { return edge.size(); }
	size_t degree(size_t x) { return graph[x].size(); }

	std::vector<edge_t> get_edge() { return edge; }

	void clear() {
		graph.clear();
		label.clear();
		edge.clear();
	}
	void swap(graph_t& r) {
		graph.swap(r.graph);
		label.swap(r.label);
		edge.swap(r.edge);
	}
};

class wl_kernel: public graph_t {
	std::vector<std::vector<size_t>> histogram;
	size_t lower;

public:
	wl_kernel(size_t n): graph_t(n) {
		lower = 0;
		histogram.resize(1);
		for(size_t i = 0; i < n; i++) histogram[0].push_back(i);
	}
	template<class InputIt> wl_kernel(InputIt first, InputIt last)
	: graph_t(first, last) {
		lower = 0;
		histogram.resize(*std::max_element(begin(label), end(label)));
		for(size_t i = 0; i < size(); i++) histogram[label[i]].push_back(i);
	}

public:
	void iterate() {
		std::vector<std::vector<size_t>> vec(size());
		for(size_t k = lower; k < histogram.size(); k++)
			for(size_t v: histogram[k])
				for(size_t u: graph[v]) vec[u].push_back(k);

		std::vector<size_t> order(size());
		std::iota(begin(order), end(order), 0);
		std::sort(begin(order), end(order), [&](size_t i, size_t j) { return vec[i] < vec[j]; });

		// std::vector<size_t> order = counting_sort(vec);

		histogram.push_back(std::vector<size_t>());
		for(size_t i = 0; i < size(); i++) {
			if(i != 0 and vec[order[i - 1]] != vec[order[i]]) {
				histogram.push_back(std::vector<size_t>());
			}
			histogram.back().push_back(order[i]);
		}
		lower = histogram.size();
	}
	void iterate(size_t k) { while(k--) iterate(); }

	std::vector<size_t> get_histogram() {
		std::vector<size_t> ret(histogram.size());
		for(size_t i = 0; i < histogram.size(); i++) ret[i] = histogram[i].size();
		return std::move(ret);
	}
};
}
