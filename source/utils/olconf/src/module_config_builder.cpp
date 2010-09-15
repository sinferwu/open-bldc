
#include <olconf/module_config_builder.hpp>
#include <olconf/module_config.hpp>
#include <olconf/abstract_module_config_runner.hpp>

#include <yamlgen/config_node.hpp>
#include <yamlgen/logging.hpp>


namespace YAMLGen { 
namespace OBLDC { 

void
ModuleConfigBuilder::parse(ConfigNode const & config) 
{
	ConfigNode root;
	ConfigNode::const_iterator root_it = config.find("config_root");
	if(root_it != config.end()) { 
		root = (*root_it).second;
	}
	else { 
		throw BuilderException("Could not find config_root in ModuleConfigBuilder");
	}
	parse_partial(root);
}

void
ModuleConfigBuilder::parse_partial(ConfigNode const & config_node) 
{
	ConfigNode::const_iterator it_modules;
	ConfigNode::const_iterator end_modules = config_node.end(); 
	for(it_modules = config_node.begin(); it_modules != end_modules; ++it_modules) 
	{ 
		::std::string module_name     = (*it_modules).first; 
		ConfigNode module_config_node = (*it_modules).second; 
		ModuleConfig module_config(module_name, module_config_node);
		m_modules.push_back(module_config);
		LOG_DEBUG_PRINT("-----------------------------------");
		LOG_DEBUG_PRINT("Building module %s", module_name.c_str());
		LOG_DEBUG_PRINT("Module section:\n");
#if defined(LOG) && LOG == DEBUG
		module_config_node.log(); 
#endif
		LOG_DEBUG_PRINT("\n");
		LOG_DEBUG_PRINT("End Module section");
	}
}

void 
ModuleConfigBuilder::run(AbstractModuleConfigRunner & runner) 
{ 
	runner.run(this); 
}

} /* namespace OBLDC */
} /* namespace YAMLGen */