
module.exports = {

    name: "ImpsApps Singleton Template",

    directory: true,

    params: ["ClassName"],

    rules: function(config) {

      return({
        items: [
          { destinationFile: config.ClassName + ".h",           sourceTemplateFile: "TEMPLATE.h"    },
          { destinationFile: config.ClassName + ".c",           sourceTemplateFile: "TEMPLATE.c"    }
        ]
      });

    }

}
