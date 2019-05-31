var utils = require('../utils/index.js');


async function getMail(siretInput) {
    var user = await utils.knex('retailer').where({
                                                  company_register: siretInput
                                                  });
    if (user.length !== 1) {
        return null;
    }
    return user[0].mail;
}

async function getTel(siretInput) {
    var user = await utils.knex('retailer').where({
                                                  company_register: siretInput
                                                  });
    if (user.length !== 1) {
        return null;
    }
    return user[0].tel;
}

async function getAddress(siretInput) {
    var user = await utils.knex('retailer').where({
                                                  company_register: siretInput
                                                  });
    if (user.length !== 1) {
        return null;
    }
    return user[0].address;
}


