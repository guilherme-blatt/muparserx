#ifndef MP_PARSER_MESSAGE_PROVIDER_H
#define MP_PARSER_MESSAGE_PROVIDER_H

#include <vector>
#include <memory>

#include "mpDefines.h"
#include "mpTypes.h"


MUP_NAMESPACE_START

  //-----------------------------------------------------------------------------------------------
  /** \brief Base class for Parser Message providing classes. */
  class ParserMessageProviderBase
  {
  friend class std::auto_ptr<ParserMessageProviderBase>;

  public:
    ParserMessageProviderBase();

    void Init();
    string_type operator[](unsigned a_iIdx) const;

  private:
    // Disable CC and assignment operator for this class and derivatives
    ParserMessageProviderBase(const ParserMessageProviderBase &ref);
    ParserMessageProviderBase& operator=(const ParserMessageProviderBase &ref);

  protected:
    std::vector<string_type>  m_vErrMsg;
    std::vector<string_type>  m_vHints;
    
    virtual ~ParserMessageProviderBase();
    virtual void InitErrorMessages() = 0;
    virtual void InitHints() = 0;
  };

  //-----------------------------------------------------------------------------------------------
  /** \brief English versions of parser messages. */
  class ParserMessageProviderEnglish : public ParserMessageProviderBase
  {
  public:
    ParserMessageProviderEnglish();

  protected:
    virtual void InitErrorMessages();
    virtual void InitHints();
  };

  //-----------------------------------------------------------------------------------------------
  /** \brief German versions of parser messages. */
  class ParserMessageProviderGerman : public ParserMessageProviderBase
  {
  public:
    ParserMessageProviderGerman();

  protected:
    virtual void InitErrorMessages();
    virtual void InitHints();
  };

MUP_NAMESPACE_END

#endif