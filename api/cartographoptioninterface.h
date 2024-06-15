#ifndef CARTOGRAPHOPTIONINTERFACE_H
#define CARTOGRAPHOPTIONINTERFACE_H

#include <string>
#include <vector>

/**
 * @brief The CartographOptionInterface class provides means for sending options between
 * Cartograph Maps and the plugin.
 */

class CartographOptionInterface
{
public:

    /**
     * @brief The OptionType enum defines the type of option value.
     */
    enum class OptionType: int {
        Int_Value     = 0,
        Double_Value  = 1,
        Bool_Value    = 2,
        String_Value  = 3,
        Select_Value  = 4
    };

    // An @Option consists of a type, a key, a name, and a value.
    class Option {
    public:
        Option(const std::string& key, const std::string& name, OptionType optionType, bool reloadMapOnChange) 
            : key(key), name(name), optionType(optionType), reloadMapOnChange(reloadMapOnChange) {}
        virtual ~Option() = default;
        std::string key;
        std::string name;
        OptionType optionType;
        bool reloadMapOnChange; // If true then the map is redrawn when the user changes the option value.
    };

    class IntOption : public Option {
    public:
        IntOption(const std::string &key, const std::string &name, int value, bool reloadMapOnChange = false, int minValue = std::numeric_limits<int>::lowest(), int maxValue = std::numeric_limits<int>::max())
            : Option(key, name, OptionType::Int_Value, reloadMapOnChange), value(value), minValue(minValue), maxValue(maxValue) {}
        int value;
        int minValue;
        int maxValue;
    };
    class DoubleOption : public Option {
    public:
        DoubleOption(const std::string& key, const std::string& name, double value, bool reloadMapOnChange = false, double minValue = std::numeric_limits<double>::lowest(), double maxValue = std::numeric_limits<double>::max())
            : Option(key, name, OptionType::Double_Value, reloadMapOnChange), value(value), minValue(minValue), maxValue(maxValue) {}
        double value;
        double minValue;
        double maxValue;
    };
    class BoolOption : public Option {
    public:
        BoolOption(const std::string& key, const std::string& name, bool value, bool reloadMapOnChange = false)
            : Option(key, name, OptionType::Bool_Value, reloadMapOnChange), value(value) {}
        bool value;
    };
    class StringOption : public Option {
    public:
        StringOption(const std::string& key, const std::string& name, const std::string& value, bool reloadMapOnChange = false)
            : Option(key, name, OptionType::String_Value, reloadMapOnChange), value(value) {}
        std::string value;
    };

    class SelectOptionEntry {
    public:
        SelectOptionEntry(const std::string& name, const std::string& value)
            : name(name), value(value){}
        std::string name;
        std::string value;
    };
    class SelectOption : public Option {
    public:
        SelectOption(const std::string& key, const std::string& name, const std::vector<SelectOptionEntry>& values, bool reloadMapOnChange = false)
            : Option(key, name, OptionType::String_Value, reloadMapOnChange), values(values) {}
        std::vector<SelectOptionEntry> values;
    };

public:
    virtual ~CartographOptionInterface() = default;

    // Methods for setting options.
    virtual void setIntOption(const std::string& key, int value) {};
    virtual void setDoubleOption(const std::string& key, double value) {};
    virtual void setBoolOption(const std::string& key, bool value) {};
    virtual void setStringOption(const std::string& key, const std::string &value) {};
    virtual void setSelectOption(const std::string& key, const std::string& value) {};

    // Get a list of options provided by the plugin.
    virtual std::vector<Option*> getOptions() const {return std::vector<Option*>(); };

};

#endif // CARTOGRAPHOPTIONINTERFACE_H
