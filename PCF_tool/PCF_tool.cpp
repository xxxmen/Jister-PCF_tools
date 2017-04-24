﻿//==============================================================================
//        This file was generated by the NX Block UI Styler
//        Created by: chenjie
//              Version: NX 10
//              Date: 02-20-2017  (Format: mm-dd-yyyy)
//              Time: 23:20 (Format: hh-mm)
//
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------ 

#include "pcf_tool.hpp"


using namespace std;
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(pcf_tool::theSession) = NULL;
UI *(pcf_tool::theUI) = NULL;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
pcf_tool::pcf_tool()
{
    try
    {
        // Initialize the NX Open C++ API environment
        pcf_tool::theSession = NXOpen::Session::GetSession();
        pcf_tool::theUI = UI::GetUI();
		workPart = theSession->Parts()->Work();
		displayPart = theSession->Parts()->Display();

		TCHAR path[MAX_PATH];
		char path_name[250];
		char dlx_name[250];
		GetModuleFileName(GetModuleHandle(TEXT("PCF_tool.dll")),path,MAX_PATH);
		TcharToChar(path,path_name);
		vector<string> splite_string;
		string temp = path_name;
		Splite(temp, ".", splite_string);
		strcpy(dlx_name, splite_string[0].c_str());
		strcat(dlx_name, ".dlx");

        theDlxFileName = dlx_name;
        theDialog = pcf_tool::theUI->CreateDialog(theDlxFileName);
        // Registration of callback functions
        theDialog->AddApplyHandler(make_callback(this, &pcf_tool::apply_cb));
        theDialog->AddOkHandler(make_callback(this, &pcf_tool::ok_cb));
        theDialog->AddUpdateHandler(make_callback(this, &pcf_tool::update_cb));
        theDialog->AddInitializeHandler(make_callback(this, &pcf_tool::initialize_cb));
        theDialog->AddDialogShownHandler(make_callback(this, &pcf_tool::dialogShown_cb));
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        throw;
    }
}

//------------------------------------------------------------------------------
// Destructor for NX Styler class
//------------------------------------------------------------------------------
pcf_tool::~pcf_tool()
{
    if (theDialog != NULL)
    {
        delete theDialog;
        theDialog = NULL;
    }
}
//------------------------------- DIALOG LAUNCHING ---------------------------------
//
//    Before invoking this application one needs to open any part/empty part in NX
//    because of the behavior of the blocks.
//
//    Make sure the dlx file is in one of the following locations:
//        1.) From where NX session is launched
//        2.) $UGII_USER_DIR/application
//        3.) For released applications, using UGII_CUSTOM_DIRECTORY_FILE is highly
//            recommended. This variable is set to a full directory path to a file 
//            containing a list of root directories for all custom applications.
//            e.g., UGII_CUSTOM_DIRECTORY_FILE=$UGII_ROOT_DIR\menus\custom_dirs.dat
//
//    You can create the dialog using one of the following way:
//
//    1. MENU BAR
//    
//        1) Add the following lines to your MenuScript file in order to
//           associate a menu bar button with your dialog.  In this
//           example, a cascade menu will be created and will be
//           located just before the Help button on the main menubar.
//           The button, SAMPLEVB_BTN is set up to launch your dialog and
//           will be positioned as the first button on your pulldown menu.
//           If you wish to add the button to an existing cascade, simply
//           add the 3 lines between MENU LAUNCH_CASCADE and END_OF_MENU
//           to your menuscript file.
//           The MenuScript file requires an extension of ".men".
//           Move the contents between the dashed lines to your Menuscript file.
//        
//           !-----------------------------------------------------------------------------
//           VERSION 120
//        
//           EDIT UG_GATEWAY_MAIN_MENUBAR
//        
//           BEFORE UG_HELP
//           CASCADE_BUTTON BLOCKSTYLER_DLX_CASCADE_BTN
//           LABEL Dialog Launcher
//           END_OF_BEFORE
//        
//           MENU BLOCKSTYLER_DLX_CASCADE_BTN
//           BUTTON SAMPLEVB_BTN
//           LABEL Display SampleVB dialog
//           ACTIONS <path of Shared library> !For example: D:\temp\SampleVB.dll
//           END_OF_MENU
//           !-----------------------------------------------------------------------------
//        
//        2) Make sure the .men file is in one of the following locations:
//        
//           - $UGII_USER_DIR/startup   
//           - For released applications, using UGII_CUSTOM_DIRECTORY_FILE is highly
//             recommended. This variable is set to a full directory path to a file 
//             containing a list of root directories for all custom applications.
//             e.g., UGII_CUSTOM_DIRECTORY_FILE=$UGII_ROOT_DIR\menus\custom_dirs.dat
//    
//------------------------------------------------------------------------------
extern "C" DllExport void  ufusr(char *param, int *retcod, int param_len)
{
    pcf_tool *thepcf_tool = NULL;
    try
    {
        thepcf_tool = new pcf_tool();
        // The following method shows the dialog immediately
        thepcf_tool->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        pcf_tool::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    if(thepcf_tool != NULL)
    {
        delete thepcf_tool;
        thepcf_tool = NULL;
    }
}

int pcf_tool::Show()
{
    try
    {
        theDialog->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        pcf_tool::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//---------------------Block UI Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void pcf_tool::initialize_cb()
{
    try
    {
        group0 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group0"));
        button0 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button0"));
        button01 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button01"));
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        pcf_tool::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void pcf_tool::dialogShown_cb()
{
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        pcf_tool::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int pcf_tool::apply_cb()
{
    int errorCode = 0;
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        pcf_tool::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int pcf_tool::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
    try
    {
		UF_initialize();
        if(block == button0)
        {
			pcf_generation pcf_generate;

			int status = ERROR_OK;
			char pcf_name[ MAX_FSPEC_BUFSIZE ] = "";

			UF_print_syslog( "Beginning PCF Generation...\n", FALSE );
			UF_UI_set_status( "Beginning PCF Generation..." );

			//find the file path and create name of pcf file with the part name
			vector<string> splite_string;
			string temp = workPart->FullPath().GetText();
			Splite(temp, ".", splite_string);
			strcpy(pcf_name, splite_string[0].c_str());
			strcat(pcf_name, ".pcf");

			displayPart->ModelingViews()->WorkView()->Fit();

			if( status == ERROR_OK )
			{
			   /*    
			   ** Create the Piping Component File (.pcf) based on the current
			   ** work part
			   */
	
				//***Add by CJ*****update the reference set
				std::vector< NXOpen::DisplayableObject*> display_obj = displayPart->ModelingViews()->WorkView()->AskVisibleObjects();
				for(std::vector<DisplayableObject*>::iterator it = display_obj.begin(); it != display_obj.end(); it++)
				{
					Assemblies::Component* component = dynamic_cast<Assemblies::Component*>(*it);
					if(component != NULL)
					{
						std::vector<NXOpen::Assemblies::Component *> components(1);
						components[0] = component;
						NXOpen::ErrorList *errorList;
						errorList = workPart->ComponentAssembly()->ReplaceReferenceSetInOwners("Entire Part", components);
					}
				}

				std::vector<Assemblies::Component*> components;
				pcf_generate.getComponents(components);

				//====find X06EA and X06EB and set the NPS and NPS_OUT for port=====
				for(int it_comp = 0; it_comp < components.size(); it_comp++)
				{
					char name[100];
					strcpy(name,components[it_comp]->DisplayName().GetText());
					char *X06EA = strstr(name, "X06EA");
					char *X06EB = strstr(name, "X06EB");

					if((X06EA != NULL) || (X06EB != NULL))
					{
						NXOpen::PartLoadStatus *partloadstatus1;
						theSession->Parts()->SetWorkComponent(components[it_comp], NXOpen::PartCollection::RefsetOptionCurrent, NXOpen::PartCollection::WorkComponentOptionVisible, &partloadstatus1);
						workPart = theSession->Parts()->Work();
						delete partloadstatus1;

						NXOpen::Routing::FittingPortCollection::iterator it_port;
						for(it_port = workPart->RouteManager()->FittingPorts()->begin();it_port != workPart->RouteManager()->FittingPorts()->end();it_port++)
						{
							Routing::FittingPort* port = dynamic_cast<Routing::FittingPort*> (*it_port);
							if(port != NULL)
							{
								if(fabs(port->Position().X)< 0.0001 && fabs(port->Position().Y)< 0.0001 && fabs(port->Position().Z)< 0.0001 )
								{
									port->SetUserAttribute("R$$NPS", -1, "NPS", NXOpen::Update::OptionNow);
								}else
								{
									port->SetUserAttribute("R$$NPS", -1, "NPS_OUT", NXOpen::Update::OptionNow);
								}
							}
						}

						NXOpen::Assemblies::Component *null_Assemblies_Component(NULL);
						NXOpen::PartLoadStatus *partloadstatus2;
						theSession->Parts()->SetWorkComponent(null_Assemblies_Component, NXOpen::PartCollection::RefsetOptionCurrent, NXOpen::PartCollection::WorkComponentOptionVisible, &partloadstatus2);
						workPart = theSession->Parts()->Work();
						delete partloadstatus2;
				
					}
				}
				//================================================================
				status = pcf_generate.create_component_file( UF_ASSEM_ask_work_part(), pcf_name ); 

				//***Add by CJ*****update the reference set
				for(std::vector<DisplayableObject*>::iterator it = display_obj.begin(); it != display_obj.end(); it++)
				{
					Assemblies::Component* component = dynamic_cast<Assemblies::Component*>(*it);
					if(component != NULL)
					{
						std::vector<NXOpen::Assemblies::Component *> components(1);
						components[0] = component;
						NXOpen::ErrorList *errorList;
						errorList = workPart->ComponentAssembly()->ReplaceReferenceSetInOwners("SOLID", components);
					}
				}
			}

			char msg[256];
			strcpy(msg, "PCF file has been generated at:\n");
			strcat(msg, pcf_name);
			uc1601(msg,1);

			if (status != ERROR_OK)
			{
			   UF_print_syslog( "Failed to create PCF!\n", FALSE );
			   UF_UI_set_status( "PCF Generation Failed" );
			}
			else
			{
			   UF_UI_set_status( "PCF Generation Complete" );
			}

			UF_print_syslog( "Exiting PCF Generation...\n", FALSE );

        }
        else if(block == button01)
        {
			pcf_generation pcf_generate;

			int status = ERROR_OK;
			UF_print_syslog( "Beginning PCF Generation...\n", FALSE );
			UF_UI_set_status( "Beginning PCF Generation..." );

			if( status == ERROR_OK )
			{
			   /*    
			   ** Create the Piping Component File (.pcf) based on the current
			   ** work part
			   */
				//fit the view
				displayPart->ModelingViews()->WorkView()->Fit();

				//get current path of the prt file
				char current_path[256];
				std::vector<string> splite_string;
				string temp = workPart->FullPath().GetText();
				Splite(temp, "\\", splite_string);
				strcpy(current_path, splite_string[0].c_str());
				strcat(current_path, "\\");
				for(int i = 1; i < splite_string.size()-1; i++)
				{
					strcat(current_path, splite_string[i].c_str());
					strcat(current_path, "\\");
				}
		
				//get all of the stocks
				NXOpen::Routing::StockCollection::iterator it_stock;
				for(it_stock = workPart->RouteManager()->Stocks()->begin() ; it_stock != workPart->RouteManager()->Stocks()->end() ; it_stock ++ )				
				{
					Routing::Stock* stocks = (Routing::Stock*) *it_stock;
					char pcf_name[256];
					char stock_name[256];

					//get feature from stock
					std::vector< NXOpen::Features::Feature * > feature = stocks->GetFeatures();
			
					if(feature.size()>0)
					{
						//get value of "TubeCallout" from feature
						 
						if(feature[0]->HasUserAttribute("TubeCallout",NXOpen::NXObject::AttributeTypeString,0))
						{
							strcpy(stock_name, feature[0]->GetStringUserAttribute("TubeCallout",0).GetLocaleText());
							strcpy(pcf_name, current_path);
							strcat(pcf_name, stock_name);
							strcat(pcf_name, ".pcf");

							//create PCF file
							status = pcf_generate.create_tube_file( UF_ASSEM_ask_work_part() , stocks->Tag() , pcf_name ); 
						}else
						{
							uc1601("The stock doesn't have the TubeCallout attribute!",1);
						}
					}else
					{
						uc1601("Can't find the feature from stock! PCF generation uncomplete!",1);
					}
				
				}
			}

			uc1601("PCF Generation Complete!",1);

			if (status != ERROR_OK)
			{
			   UF_print_syslog( "Failed to create PCF!\n", FALSE );
			   UF_UI_set_status( "PCF Generation Failed" );
			}
			else
			{
			   UF_UI_set_status( "PCF Generation Complete" );
			}
			UF_print_syslog( "Exiting PCF Generation...\n", FALSE );
    
        }
		UF_terminate();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        pcf_tool::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int pcf_tool::ok_cb()
{
    int errorCode = 0;
    try
    {
        errorCode = apply_cb();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        pcf_tool::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

void pcf_tool::Splite(string input_str, char* symbol, vector<string>& output_str)
{
	const int len = strlen(symbol);
	size_t index = 0;  
    size_t pos = input_str.find(symbol,index); 
	while(pos != string::npos)  
    {  
        string ss = input_str.substr(index,pos-index);  
		if(!ss.empty())
		{
			output_str.push_back(ss); 
		}
        index = pos + len;  
        pos = input_str.find(symbol,index);  
    }
	if((index+1) < input_str.length())  
    {  
        string ss = input_str.substr(index,input_str.length() - index);  
		if(!ss.empty())
		{
			output_str.push_back(ss); 
		}
    }  
	return;
}

void pcf_tool::TcharToChar(const TCHAR * tchar, char * _char)
{
    int iLength;
    //获取字节长度   
    iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
    //将tchar值赋给_char    
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
//------------------------------------------------------------------------------
//Function Name: GetBlockProperties
//Description: Returns the propertylist of the specified BlockID
//------------------------------------------------------------------------------
PropertyList* pcf_tool::GetBlockProperties(const char *blockID)
{
    return theDialog->GetBlockProperties(blockID);
}
