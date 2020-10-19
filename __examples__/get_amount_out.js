
// calculations
const fee = 30;
const amount_in = 3734534447974;
const reserve_in = 33593153629677144;
const reserve_out = 899196436;

const amount_in_with_fee = amount_in * (10000 - fee);
const numerator = amount_in_with_fee * reserve_out;
const denominator = (reserve_in * 10000) + amount_in_with_fee;
const amount_out = numerator / denominator;
console.log(amount_out);
// => 99652.29296384696

// 373786282494
// 373786282495