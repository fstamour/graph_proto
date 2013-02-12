#include <iostream>
#include <stdexcept>

/**
 * @author Francis St-Amour
 * @date   11 feb 2013
 **/



template< typename T >
class Graph {
private:
  size_t m_size;

//For dev purpose:
//protected:

	bool **m_adjacencyMatrix; //This could use an optimisation...
	//set< pair< size_t, size_t > >;
	//sparseMatrix ...

	T* m_values;

public:

	class value_iterator {
		size_t m_pos;

		Graph* m_graph;
	public:

		//Ctor
		value_iterator( Graph* graph = nullptr, size_t pos = -1 ):
			m_pos(pos),
			m_graph(graph)
			{}

		void next() {
			m_pos++;
			if( m_pos >= m_graph->m_size )
				m_pos = -1;
		}

		inline void operator++() { next(); }

		inline operator bool() const { return m_pos != -1; }

		inline T& operator*() { return m_graph->m_values[m_pos]; }
		inline const T& operator*() const { return m_graph->m_values[m_pos]; }

		inline bool operator==( const value_iterator& it) const {
			return m_pos == it.m_pos;
		}
	};

	Graph(size_t size);
	virtual ~Graph();

	inline size_t size() const { return m_size; }

	//@todo const or not to const?
	value_iterator begin(size_t pos = 0) {
		if( pos >= m_size )
			throw std::out_of_range("Graph::begin(pos) out of range.");
		return value_iterator( this, pos);
	}

	/*consexpr | inline */
	value_iterator end() {
		return value_iterator();
	}



	bool& operator() ( size_t from, size_t to ) {
		//Maybe throw something...
		return m_adjacencyMatrix[from][to];
	}

	bool operator() ( size_t from, size_t to ) const {
		//Maybe throw something...
		return m_adjacencyMatrix[from][to];
	}


	//This is a kind of iterator...
	///@todo Getter/Setter...
	class Node {

		size_t m_nodeIndex;
		Graph* m_graph;

		class edge_iterator {
			size_t m_pos;

			Graph* m_graph;
			Node* m_node;

		protected:

			inline size_t findNext( size_t from ) {
				for(size_t i = from; i < m_graph->m_size; ++i) {
					if( m_graph->m_adjacencyMatrix[m_node->m_nodeIndex][i] == true) {
						return i;
					}
				}
				return -1;
			}

		public:

			//Ctor
			edge_iterator(Graph* graph = nullptr, Node* node = nullptr):
				m_pos(0),
				m_graph(graph),
				m_node(node)
				{
					if( m_graph && m_node ) {
						m_pos = findNext(0);
					} else {
						m_pos = -1;
					}
				}

			void next() {
				m_pos = findNext(++m_pos);
			}

			inline void operator++() { next(); }

			inline operator bool() const { return m_pos != -1; }

			inline T& operator*() { return m_graph->m_values[m_pos]; }
			inline const T& operator*() const { return m_graph->m_values[m_pos]; }

			inline bool operator==(const edge_iterator& it) const {
				return m_pos == it.m_pos;
			}
		};

	public:


		Node(Graph* graph, size_t nodeIndex ):
			m_graph(graph),
			m_nodeIndex(nodeIndex)
			{}

		edge_iterator begin() {
			return edge_iterator( m_graph, this);
		}

		/*consexpr | inline */
		edge_iterator end() const {
			return edge_iterator();
		}
	};

	inline Node getNode( size_t n ) {
		if( n >= m_size )
			throw std::out_of_range("Graph::getNode(n) out of range.");
		return Node(this, n);
	}

	inline T& get( size_t n ) {
		if( n >= m_size )
			throw std::out_of_range("Graph::getNode(n) out of range.");
		return m_values[n];
	}

	inline const T get( size_t n ) const {
		if( n >= m_size )
			throw std::out_of_range("Graph::getNode(n) out of range.");
		return m_values[n];
	}



};

template< typename T >
Graph<T>::Graph(size_t size):
	m_size(size)
{
	m_adjacencyMatrix = new bool* [m_size];
	for(int i=0; i < m_size; ++i) {
		m_adjacencyMatrix[i] = new bool[m_size];
		for(int j=0; j < m_size; ++j)
			m_adjacencyMatrix[i][j] = false;
	}

	m_values= new T[m_size];
}

template< typename T >
Graph<T>::~Graph() {
	for(int i=0; i < m_size; ++i)
		delete[] m_adjacencyMatrix[i];
	delete[] m_adjacencyMatrix;

	delete[] m_values;
}



using namespace std;


int main(int argc, char** argv) {

	Graph<int> g(10);

	//Init
	int i = 0;
	for( int& x : g ) {
		x = i + 1;
		for( size_t j =0; j < g.size(); ++j ) {
			if( x % (int)(j + 1) == 0 )
				g(i,j) = true;
		}
		++i;
	}



	cout << "--- Printing the adjacency matrix ---\n";
	//Printing values (top)
	cout << "\t";
	for( int x : g )
		cout << x << "\t";
	cout << "\n";

	//Printing the adjacency matrix
	for( size_t i =0; i < g.size(); ++i ) {
		cout << g.get(i) << "\t";
		for( size_t j =0; j < g.size(); ++j ) {
			cout <<  g(i,j) << "\t";
		}
		cout << "\n";
	}
	cout << "\n";


	cout << "--- Printing values ---\n";
	{
		cout << "First method:\n";
		auto it = g.begin();
		while( it ) {
			cout << (*it) << "\n";
			it.next();
		}

		cout << "\nSecond method:\n";
		for( int x : g ) {
			cout << x << "\n";
		}
	}
	cout << "\n";

	cout << "Divisor(s) of 10:\n";
	{
		cout << "First method:\n";
		auto it = g.getNode(9).begin();
		while( it ) {
			cout << (*it) << "\n";
			it.next();
		}

		cout << "\nSecond method:\n";
		for( int div : g.getNode( 9 ) ) {
			cout << div << "\n";
		}
	}


	return 0;
}
