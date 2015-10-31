#include "common.h"

void printObj(const rapidjson::Value& data) {
    if (data.IsObject()) {
        for (rapidjson::Value::ConstMemberIterator itr = data.MemberBegin(); itr != data.MemberEnd(); ++itr) {
            printf("obj[%s] = ", itr->name.GetString());
            switch (itr->value.GetType()) {
                case 0:
                    printf("IsNull!");
                    break;
                case 1:
                    printf("False");
                    break;
                case 2:
                    printf("True");
                    break;
                case 3:
                    // IsObject
                    printf("{\n");
                    printObj(itr->value);
                    printf("}\n");
                    break;
                case 4:
                    // IsArray
                    printf("[\n");
                    printObj(itr->value);
                    printf("]\n");
                    break;
                case 5:
                    printf("%s", itr->value.GetString());
                    break;
                case 6:
                    printf("%d", itr->value.GetInt());
                    break;
            }

            printf("\n");
        }
    } else {
        for (rapidjson::SizeType i = 0; i < data.Size(); i++) {
            printf("{\n");
            printObj(data[i]);
            printf("}, \n");
        }
    }
}

