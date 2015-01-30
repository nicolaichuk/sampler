
#include "gibbs.h"
#include "gtest/gtest.h"
#include "io/binary_parser.h"
#include "dstruct/factor_graph/factor_graph.h"
#include "dstruct/factor_graph/factor.h"
#include "io/partition.h"
#include <fstream>

using namespace dd;

TEST(PartitionTest, variables) {
	dd::FactorGraph fg(200, 200, 200, 1);
	Partition partition(3, 200, "./test/partition/graph.partition.variables", 
		"./test/partition/graph.factors");

	partition.partition_variables("./test/partition/graph.variables");
	read_variables("./test/partition/graph.variables.part0", fg);
	read_variables("./test/partition/graph.variables.part1", fg);
	read_variables("./test/partition/graph.variables.part2", fg);

	partition.partition_factors("./test/partition/graph.factors");
	read_factors("./test/partition/graph.factors.part0", fg);
	read_factors("./test/partition/graph.factors.part1", fg);
	read_factors("./test/partition/graph.factors.part2", fg);

	partition.partition_edges("./test/partition/graph.edges");
	read_edges("./test/partition/graph.edges.part0", fg);
	read_edges("./test/partition/graph.edges.part1", fg);
	read_edges("./test/partition/graph.edges.part2", fg);

	for (int i = 0; i < 3; i++) {
		std::cout << partition.metas[i].num_variables << " " << partition.metas[i].num_factors << " "
			<< partition.metas[i].num_edges << std::endl;
	}
}

TEST(PartitionTest, integration) {

	const char* argv[28] = {
		"dw", "gibbs", "-w", "./test/partition/graph.weights", "-v", "./test/partition/graph.variables", 
		"-f", "./test/partition/graph.factors", "-e", "./test/partition/graph.edges", "-m", "./test/partition/graph.meta",
		"-o", ".", "-l", "3", "-i", "3", "-s", "1", "--alpha", "0.1", "--num_partitions",
		"3", "--partition_variableids_file", "./test/partition/graph.partition.variables", "--partition_factorids_file", 
		"./test/partition/graph.partition.factors"
	};

	dd::CmdParser cmd_parser = parse_input(28, (char **)argv);
	gibbs(cmd_parser);

}
