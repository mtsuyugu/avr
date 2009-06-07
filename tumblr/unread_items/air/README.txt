* How to build and run.
    0. Prerequisite, you have to install these;
        * Flex 3 SDK: http://www.adobe.com/cfusion/entitlement/index.cfm?e=flex3sdk
        * Adobe AIR SDK: http://www.adobe.com/jp/products/air/tools/sdk/
    1. Download 'Flash Net Comport Connector'
        http://www.hatayan.org/software/fncc/index.php
    2. Install 'Flash Net Comport Connector' to [top_of_repository]\air\lib. 
       After that, you will see the file;
         [top_of_repository]\air\lib\org\hatayan\flashNetComportConnector\SerialPort.as
    3. To compile it, from command prompt 
         amxmlc TumblrUnread.mxml
    4. To run it, from comman prompt;
         adl TumblrUnread.xml