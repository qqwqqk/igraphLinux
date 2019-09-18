#include <stdio.h>
#include <igraph.h>
#include <string.h>

#define INFOMAP_TRIALS 0x4

int infomap(const char* path)
{
	char readheader[200] = "sourcedata/Edgelist_";
	char writeheader[200] = "targetdata/Informap_";
	strcat_s(readheader, 200, path);
	strcat_s(writeheader, 200, path);

	const char* readpath = readheader;
	const char* writepath = writeheader;

	//�ߴ�ŵ��ļ�,�ո�ָ�
	FILE *edgeListFile, *ResultFile;
	fopen_s(&edgeListFile, readpath, "r");
	fopen_s(&ResultFile, writepath, "w");

	igraph_t wbNetwork;
	igraph_real_t Q_value;
	igraph_real_t codelength;
	igraph_vector_t membership;
	long int i;
	long int no_of_nodes;
	long int no_of_edges;
	int rstCode, count = 0;
	igraph_vector_t gtypes, vtypes, etypes;
	igraph_strvector_t gnames, vnames, enames;
	/* turn on attribute handling */
	igraph_i_set_attribute_table(&igraph_cattribute_table);

	//��ʼ������
	igraph_vector_init(&membership, 0);

	//if (argc < 2){printf("Usage: %s <inputRelationFile> \n", argv[0]);exit(1);}

	//���ļ��ж���ͼ
	igraph_read_graph_ncol(&wbNetwork,
		edgeListFile,
		0,  /*Ԥ����Ľڵ�����*/
		1, /*����ڵ�����*/
		IGRAPH_ADD_WEIGHTS_NO,  /*�Ƿ񽫱ߵ�Ȩ��Ҳ����*/
		0  /*0��ʾ����ͼ*/
		);
	fclose(edgeListFile);
	igraph_simplify(&wbNetwork, 1, 1, 0);

	igraph_vector_init(&gtypes, 0);
	igraph_vector_init(&vtypes, 0);
	igraph_vector_init(&etypes, 0);
	igraph_strvector_init(&gnames, 0);
	igraph_strvector_init(&vnames, 0);
	igraph_strvector_init(&enames, 0);

	igraph_cattribute_list(&wbNetwork, &gnames, &gtypes, &vnames, &vtypes,
		&enames, &etypes);

	no_of_nodes = igraph_vcount(&wbNetwork);
	no_of_edges = igraph_ecount(&wbNetwork);
	printf("Graph node numbers: %d \n", no_of_nodes);
	printf("Graph edge numbers: %d \n", no_of_edges);


	//��ӡ������ID��ڵ�ID�Ķ�Ӧ����
	/*
	if (igraph_cattribute_has_attr(&wbNetwork, IGRAPH_ATTRIBUTE_VERTEX, "name")){
	printf("Vertex names: ");
	for (i = 0; i<no_of_nodes; i++) {
	printf("Vertex ID: %d -> Vertex Name: %s \n", i, igraph_cattribute_VAS(&wbNetwork, "name", i));
	}
	}
	else{
	printf("The Graph does not have attribute of name \n");
	}
	*/

	//����������㷨��������������ṹ����
	rstCode = igraph_community_infomap(&wbNetwork,
		/*edge weights*/ 0, 0,
		INFOMAP_TRIALS,  /*������ߵĲ���*/
		&membership,
		&codelength/*ÿ���ڵ������community���*/);
	if (rstCode != 0){
		printf("Error dealing with finding communities");
		return 1;
	}
	else{
		printf("Finding communities success! \n");
	}

	//��ӡ��ģ����ݱ�Ĺ���
	/*
	printf("Merges:\n");
	for (i = 0; i<igraph_matrix_nrow(&merges); i++) {
	printf("%2.1li + %2.li -> %2.li (modularity %4.2f)\n",
	(long int)MATRIX(merges, i, 0),
	(long int)MATRIX(merges, i, 1),
	no_of_nodes + i,
	VECTOR(modularity)[i]);
	}
	*/


	for (i = 0; i<igraph_vector_size(&membership); i++){
		// printf("node: %d belongs to community:%g \n", i + 1, VECTOR(membership)[i]);
		fprintf(ResultFile, "%s\t%g\n", igraph_cattribute_VAS(&wbNetwork, "name", i), VECTOR(membership)[i]);
		count = count>(int) VECTOR(membership)[i] ? count : (int)VECTOR(membership)[i];
	}

	fclose(ResultFile);

	rstCode = igraph_modularity(&wbNetwork,
		/* ��Ա��ϵ */&membership,
		/* ģ��� */&Q_value,
		/* ����Ȩ�� */NULL);

	printf("community number��%d \t modularity:%g \n", count + 1, Q_value);

	igraph_vector_destroy(&membership);

	igraph_vector_destroy(&gtypes);
	igraph_vector_destroy(&vtypes);
	igraph_vector_destroy(&etypes);
	igraph_strvector_destroy(&gnames);
	igraph_strvector_destroy(&vnames);
	igraph_strvector_destroy(&enames);

	igraph_destroy(&wbNetwork);

	return 0;
}