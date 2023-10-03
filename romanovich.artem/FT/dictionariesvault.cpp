#include "dictionariesvault.h"
std::shared_ptr< romanovich::DictionariesVault::value_t > romanovich::DictionariesVault::instance()
{
  static std::shared_ptr< value_t > ptrVault_ = nullptr;
  if (!ptrVault_)
  {
    ptrVault_ = std::make_shared< value_t >();
  }
  return ptrVault_;
}
