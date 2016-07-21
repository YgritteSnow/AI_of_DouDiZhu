#ifndef __DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__
#define __DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__

/************************************************************************/
/* ֻѰ�ҿ��Եõ����ߵ�һ�ַ��������������֦���ٴ���                   */
/* �������������ֻ���ӽڵ㲻���ٽڵ㣬�ɽڵ��Լ��ͷ��Լ��ͺ���			*/
/************************************************************************/

#include <deque>
#include <vector>
#include <iostream>
#include "quick_micros.h"

// �����С�� - �ڵ�
class MinMaxTreeNodeBase
{
public:
	MinMaxTreeNodeBase(){};
	virtual ~MinMaxTreeNodeBase(){
		DEBUG_TRACE_FUNC("MinMaxTreeNodeBase");
		DEBUG_LOG(m_vec_children.size());
		for( auto it = m_vec_children.begin(); it != m_vec_children.end(); ++it ) {
			delete (*it);
			*it = NULL;
		}
		m_vec_children.clear();
		DEBUG_TRACE_FUNC("MinMaxTreeNodeBase");
	};

	void AddChildren( MinMaxTreeNodeBase* p_children ){
		m_vec_children.push_back( p_children );
	}
	std::vector< MinMaxTreeNodeBase* >::iterator FirstChild(){ return m_vec_children.begin(); }
	std::vector< MinMaxTreeNodeBase* >::iterator LastChild(){ return m_vec_children.end(); }

	virtual void Print() = 0;
	virtual void GenerateChildren() = 0;
	virtual bool isUseful(){ return m_curIsMax; }
	virtual bool isAlreadyMinMax(){ return m_isNeedAllMax == m_curIsMax;} // ��Ϊ����� isNeed �Ƕ��Լ��ĺ��Ӷ��ԣ����Դ˴����Լ����෴�ģ�����Ӧ������ȡ�

	bool m_isNeedAllMax;
	bool m_curIsMax;

protected:
	std::vector< MinMaxTreeNodeBase* > m_vec_children;

};

// �����С�� - ����
template < typename TreeNode >
class MinMaxTree
{
public:
	typedef TreeNode* TreeNodePtr;
	MinMaxTree():m_root(NULL){}
	virtual ~MinMaxTree(){DEBUG_TRACE_FUNC("MinMaxTree");
		delete m_root;
		m_root = NULL;
	}

	void AddNode( TreeNodePtr father, TreeNodePtr children ){
		father->AddChildren( children );
	}

protected:
	TreeNodePtr m_root;
};

template < typename TreeNode >
class DecidingTree : public MinMaxTree< TreeNode >
{
public:
	DecidingTree(){};
	virtual ~DecidingTree(){DEBUG_TRACE_FUNC("DecidingTree");}

	void StartGenerate(){
		m_root->GenerateChildren();
	}

	void Print(){
		std::deque< MinMaxTreeNodeBase* > temp_stack;
		temp_stack.push_back( m_root );

		while( !temp_stack.empty() )
		{
			MinMaxTreeNodeBase* cur_node = temp_stack.front();
			temp_stack.pop_front();

			if( !cur_node->isUseful() )
			{
				continue;
			}

			cur_node->Print();
			for( auto it = cur_node->FirstChild(); it != cur_node->LastChild(); ++it )
			{
				if( (*it)->isUseful() )
				{
					temp_stack.push_back( (*it) );
					break;
				}
			}
		}
	}
};

#endif 