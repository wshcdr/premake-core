/**
 * \file   vs2005_project_tests.cpp
 * \brief  Automated tests for VS2005 project processing.
 * \author Copyright (c) 2008 Jason Perkins and the Premake project
 */

#include "premake.h"
#include "action/tests/action_tests.h"
extern "C" {
#include "action/vs200x/vs200x_project.h"
}

struct Fx2005Project : FxAction
{
	Fx2005Project()
	{
		session_set_action(sess, "vs2005");
	}
};


SUITE(action)
{
	TEST_FIXTURE(Fx2005Project, Vs2005_VisualStudioProject)
	{
		vs200x_project_element(sess, prj, strm);
		CHECK_EQUAL(
			"<VisualStudioProject\n"
			"\tProjectType=\"Visual C++\"\n"
			"\tVersion=\"8.00\"\n"
			"\tName=\"MyProject\"\n"
			"\tProjectGUID=\"{AE2461B7-236F-4278-81D3-F0D476F9A4C0}\"\n"
			"\tRootNamespace=\"MyProject\"\n"
			"\tKeyword=\"Win32Proj\"\n"
			"\t>\n",
			buffer);
	}


	TEST_FIXTURE(Fx2005Project, Vs2005_ToolFiles)
	{
		vs200x_project_tool_files(sess, prj, strm);
		CHECK_EQUAL(
			"\t<ToolFiles>\n"
			"\t</ToolFiles>\n"
			"\t<Configurations>\n",
			buffer);
	}


	TEST_FIXTURE(Fx2005Project, VCCLCompilerTool)
	{
		vs200x_project_vc_cl_compiler_tool(sess, prj, strm);
		CHECK_EQUAL(
			"\t\t\t<Tool\n"
			"\t\t\t\tName=\"VCCLCompilerTool\"\n"
			"\t\t\t\tOptimization=\"0\"\n"
			"\t\t\t\tMinimalRebuild=\"true\"\n"
			"\t\t\t\tBasicRuntimeChecks=\"3\"\n"
			"\t\t\t\tRuntimeLibrary=\"3\"\n"
			"\t\t\t\tUsePrecompiledHeader=\"0\"\n"
			"\t\t\t\tWarningLevel=\"3\"\n"
			"\t\t\t\tDetect64BitPortabilityProblems=\"true\"\n"
			"\t\t\t\tDebugInformationFormat=\"4\"\n"
			"\t\t\t/>\n",
			buffer);
	}


	TEST_FIXTURE(Fx2005Project, VCLinkerTool)
	{
		vs200x_project_vc_linker_tool(sess, prj, strm);
		CHECK_EQUAL(
			"\t\t\t<Tool\n"
			"\t\t\t\tName=\"VCLinkerTool\"\n"
			"\t\t\t\tLinkIncremental=\"2\"\n"
			"\t\t\t\tGenerateDebugInformation=\"true\"\n"
			"\t\t\t\tSubSystem=\"1\"\n"
			"\t\t\t\tEntryPointSymbol=\"mainCRTStartup\"\n"
			"\t\t\t\tTargetMachine=\"1\"\n"
			"\t\t\t/>\n",
			buffer);
	}


	TEST_FIXTURE(Fx2005Project, References)
	{
		vs200x_project_references(sess, prj, strm);
		CHECK_EQUAL(
			"\t</Configurations>\n"
			"\t<References>\n"
			"\t</References>\n",
			buffer);
	}
}